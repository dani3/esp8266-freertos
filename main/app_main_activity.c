/**
 * @file app_main_activity.c
 * @author Daniel Mancebo (daniel.m.aldea@hotmail.com)
 *
 * @brief
 */

#include "app_main_activity.h"

#include <assert.h>
#include <string.h>

#include "FreeRTOS.h"
#include "portable.h"
#include "task.h"

#include "esp_log.h"

#include "apps/app_led.h"
#include "core/events.h"

// * ----------------------------------------------------------------------------------------------
// * Typedefs and defines
// * ----------------------------------------------------------------------------------------------

#define LOG_TAG "APP_MAIN_ACTIVITY"

#define MAX_NUM_SUBSCRIBERS 16

typedef struct {
    core_event_group_t group;
    int id;
    int target_time;
} event_t;

typedef struct event_queue_entry_t event_queue_entry_t;

struct event_queue_entry_t {
    event_queue_entry_t *prev;
    event_queue_entry_t *next;
    event_t event;
};

// * ----------------------------------------------------------------------------------------------
// * Private Functions Prototypes
// * ----------------------------------------------------------------------------------------------

static void _init();
static event_queue_entry_t *_get_next_event();
static void _notify_subscribers(core_event_group_t group_id, int id);
static void _remove_event(event_queue_entry_t *event);

// * ----------------------------------------------------------------------------------------------
// * Private Variables
// * ----------------------------------------------------------------------------------------------

// List of event subscribers.
static app_activity_handler_t _subscribers[MAX_NUM_SUBSCRIBERS];
static int _num_subscribers;

// Event queue.
static event_queue_entry_t *_event_queue;

// * ----------------------------------------------------------------------------------------------
// * Private Functions
// * ----------------------------------------------------------------------------------------------

static void _init()
{
    memset(_subscribers, 0, sizeof(_subscribers));
    _num_subscribers = 0;
    _event_queue = NULL;
}

static event_queue_entry_t *_get_next_event()
{
    event_queue_entry_t *aux = _event_queue;
    while (aux != NULL) {
        if (aux->event.target_time == 0) {
            break;
        }

        aux = aux->next;
    }

    return aux;
}

static void _notify_subscribers(core_event_group_t group_id, int id)
{
    for (int i = 0; i < _num_subscribers; ++i) {
        bool consumed = _subscribers[i](group_id, id);
        if (consumed) {
            break;
        }
    }
}

static void _remove_event(event_queue_entry_t *event)
{
    // It's the first event in the queue.
    if (event == _event_queue) {
        _event_queue = event->next;
        if (_event_queue != NULL) {
            _event_queue->prev = NULL;
        }
    } else {
        event->prev->next = event->next;
        // It's not the last one.
        if (event->next != NULL) {
            event->next->prev = event->prev;
        }
    }

    free(event);
}

// * ----------------------------------------------------------------------------------------------
// * Public Functions
// * ----------------------------------------------------------------------------------------------

void app_main_activity_start(void *params)
{
    ESP_LOGI(LOG_TAG, "initializing activity...");
    _init();
    ESP_LOGI(LOG_TAG, "initializing activity... ok");

    // Push an initial event to notify that the system is initialized.
    app_main_activity_send_event(CORE_EVENT_GROUP_SYSTEM, APP_MAIN_ACTIVITY_ON_CREATE, 0);

    ESP_LOGI(LOG_TAG, "initializing apps...");
    // Apps initialization
    app_led_init();
    ESP_LOGI(LOG_TAG, "initializing apps... ok");

    for (;;) {
        vTaskDelay(10 / portTICK_PERIOD_MS);

        event_queue_entry_t *aux = _get_next_event();

        if (aux == NULL) {
            continue;
        }

        _notify_subscribers(aux->event.group, aux->event.id);
        _remove_event(aux);
    }
}

void app_main_activity_register(app_activity_handler_t handler)
{
    assert(handler != NULL);
    assert(_num_subscribers + 1 <= MAX_NUM_SUBSCRIBERS);

    ESP_LOGI(LOG_TAG, "Registering subscriber number=[%d]", (int)_num_subscribers);

    _subscribers[_num_subscribers] = handler;
    _num_subscribers++;
}

void app_main_activity_send_event(core_event_group_t event_group, int event_id, int delay_ms)
{
    ESP_LOGI(
        LOG_TAG, "Sending event with group=[%d], id=[%d] in %dms", event_group, event_id, delay_ms);

    event_queue_entry_t *e = (event_queue_entry_t *)malloc(sizeof(event_queue_entry_t));
    assert(e != NULL);

    e->next = NULL;
    e->prev = NULL;
    e->event.group = event_group;
    e->event.id = event_id;
    /// @todo
    e->event.target_time = 0;

    // No events in the queue
    if (_event_queue == NULL) {
        _event_queue = e;
        return;
    }

    e->next = _event_queue;
    _event_queue->prev = e;
    _event_queue = e;
}
