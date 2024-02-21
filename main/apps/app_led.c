/**
 * @file app_main_activity.c
 * @author Daniel Mancebo (daniel.m.aldea@hotmail.com)
 *
 * @brief
 */

#include "app_main_activity.h"

#include "apps/app_led.h"
#include "core/events.h"

#include <stdbool.h>

// * ----------------------------------------------------------------------------------------------
// * Typedefs and defines
// * ----------------------------------------------------------------------------------------------

// * ----------------------------------------------------------------------------------------------
// * Private Functions Prototypes
// * ----------------------------------------------------------------------------------------------

static bool _event_handler(core_event_group_t event_group, size_t event_id);
static bool _led_event_handler(app_led_event_id_t event_id);

// * ----------------------------------------------------------------------------------------------
// * Private Variables
// * ----------------------------------------------------------------------------------------------

// * ----------------------------------------------------------------------------------------------
// * Private Functions
// * ----------------------------------------------------------------------------------------------

static bool _led_event_handler(app_led_event_id_t event_id) {
    switch (event_id) {
        case APP_LED_EVENT_ID_ON: {
        } break;

        case APP_LED_EVENT_ID_OFF: {
        } break;
    }

    return true;
}

/**
 * @brief
 *
 * @param event_group
 * @param event_id
 * @return true
 * @return false
 */
static bool _event_handler(core_event_group_t event_group, size_t event_id) {
    bool ret = false;
    switch (event_group) {
        case CORE_EVENT_GROUP_LED: {
            ret = _led_event_handler((app_led_event_id_t)event_id);
        } break;

        default:
            break;
    }

    return ret;
}

// * ----------------------------------------------------------------------------------------------
// * Public Functions
// * ----------------------------------------------------------------------------------------------

void app_led_init() {
    app_main_activity_register(_event_handler);
}
