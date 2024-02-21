/**
 * @file app_main_activity.c
 * @author Daniel Mancebo (daniel.m.aldea@hotmail.com)
 *
 * @brief
 */

#include "app_main_activity.h"
#include <string.h>

#include "FreeRTOS.h"
#include "portable.h"
#include "task.h"

#include "esp_err.h"
#include "esp_log.h"

#include "apps/app_led.h"
#include "core/events.h"

// * ----------------------------------------------------------------------------------------------
// * Typedefs and defines
// * ----------------------------------------------------------------------------------------------

#define LOG_TAG "APP_MAIN_ACTIVITY"

#define MAX_NUM_SUBSCRIBERS 32
#define MAX_NUM_EVENTS      1024

typedef struct {
    core_event_group_t group;
    size_t id;
    size_t target_time;
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

void _init();

// * ----------------------------------------------------------------------------------------------
// * Private Variables
// * ----------------------------------------------------------------------------------------------

// List of event subscribers.
static app_activity_handler_t _subscribers[MAX_NUM_SUBSCRIBERS];
static size_t _num_subscribers;

// Event queue.
static event_queue_entry_t *_event_queue;

// * ----------------------------------------------------------------------------------------------
// * Private Functions
// * ----------------------------------------------------------------------------------------------

void _init()
{
    memset(_subscribers, 0, sizeof(_subscribers));
    _num_subscribers = 0;
    _event_queue = NULL;
}

// * ----------------------------------------------------------------------------------------------
// * Public Functions
// * ----------------------------------------------------------------------------------------------

void app_main_activity_start(void *params)
{
    ESP_LOGI(LOG_TAG, "Starting %s", __FUNCTION__);

    // System app initialization
    _init();

    // Apps initialization
    app_led_init();

    // Send an initial event to notify that the system is initialized.
    app_main_activity_send_event(CORE_EVENT_GROUP_SYSTEM, APP_MAIN_ACTIVITY_ON_CREATE, 0);

    for (;;) {
        event_queue_entry_t *aux = _event_queue;
        while (aux != NULL) {
            if (aux->event.target_time == 0) {
                break;
            }

            aux = aux->next;
        }

        if (aux != NULL) {
            // Call callbacks with the event.
            for (int i = 0; i < _num_subscribers; ++i) {
                bool consumed = _subscribers[i](aux->event.group, aux->event.id);
                if (consumed) {
                    break;
                }
            }

            // It's the first event in the queue.
            if (aux == _event_queue) {
                _event_queue = aux->next;
                _event_queue->prev = NULL;
            } else {
                aux->prev->next = aux->next;
                // It's not the last one.
                if (aux->next != NULL) {
                    aux->next->prev = aux->prev;
                }
            }

            vPortFree(aux);
        }

        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}

void app_main_activity_register(app_activity_handler_t handler)
{
    ESP_ERROR_CHECK(handler != NULL);

    for (int i = 0; i < MAX_NUM_SUBSCRIBERS; ++i) {
        if (_subscribers[i] != NULL) {
            _subscribers[i] = handler;
            _num_subscribers++;
        }
    }
}

void app_main_activity_send_event(core_event_group_t event_group, size_t event_id, size_t delay_ms)
{
    event_queue_entry_t *e = (event_queue_entry_t *)pvPortMalloc(sizeof(event_t));

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
    e->prev = NULL;
    _event_queue->prev = e;
    _event_queue = e;
}
