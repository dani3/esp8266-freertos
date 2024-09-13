/**
 * @file app_led_activity.c
 * @author Daniel Mancebo (daniel.m.aldea@hotmail.com)
 *
 * @brief
 */

#include "app_main_activity.h"

#include "apps/app_led.h"
#include "core/events.h"

#include "esp_log.h"

#include <stdbool.h>

// * ----------------------------------------------------------------------------------------------
// * Typedefs and defines
// * ----------------------------------------------------------------------------------------------

#define LOG_TAG "APP_LED"

// * ----------------------------------------------------------------------------------------------
// * Private Functions Prototypes
// * ----------------------------------------------------------------------------------------------

static bool _event_handler(core_event_group_t event_group, int event_id);
static bool _led_event_handler(app_led_event_id_t event_id);

// * ----------------------------------------------------------------------------------------------
// * Private Variables
// * ----------------------------------------------------------------------------------------------

// * ----------------------------------------------------------------------------------------------
// * Private Functions
// * ----------------------------------------------------------------------------------------------

static bool _led_event_handler(app_led_event_id_t event_id)
{
    switch (event_id) {
        case APP_LED_EVENT_ID_ON: {
            ESP_LOGI(LOG_TAG, "APP_LED_EVENT_ID_ON");
        } break;

        case APP_LED_EVENT_ID_OFF: {
            ESP_LOGI(LOG_TAG, "APP_LED_EVENT_ID_OFF");
        } break;
    }

    return true;
}

/**
 * @brief
 *
 * @param event_group
 * @param event_id
 * @return
 */
static bool _event_handler(core_event_group_t event_group, int event_id)
{
    bool ret = false;

    switch (event_group) {
        case CORE_EVENT_GROUP_LED: {
            ESP_LOGI(LOG_TAG, "CORE_EVENT_GROUP_LED");
            ret = _led_event_handler((app_led_event_id_t)event_id);
        } break;

        case CORE_EVENT_GROUP_SYSTEM: {
            ESP_LOGI(LOG_TAG, "CORE_EVENT_GROUP_SYSTEM");
            app_main_activity_send_event(CORE_EVENT_GROUP_LED, APP_LED_EVENT_ID_ON, 0);
        } break;

        default:
            break;
    }

    return ret;
}

// * ----------------------------------------------------------------------------------------------
// * Public Functions
// * ----------------------------------------------------------------------------------------------

void app_led_init()
{
    ESP_LOGI(LOG_TAG, "initializing app...");

    app_main_activity_register(_event_handler);

    ESP_LOGI(LOG_TAG, "initializing app... ok");
}
