/**
 * @file app_led_activity.c
 * @author Daniel Mancebo (daniel.m.aldea@hotmail.com)
 *
 * @brief Implementation of the app that handles the LED.
 */

#include "app_main_activity.h"

#include "apps/app_led.h"
#include "core/events.h"

#include "esp_log.h"
#include "gpio.h"

#include <stdbool.h>

// * ----------------------------------------------------------------------------------------------
// * Typedefs and defines
// * ----------------------------------------------------------------------------------------------

#define LOG_TAG "APP_LED"

#define LED_OFF 1
#define LED_ON  0

#define LED_PIN GPIO_NUM_2

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

/**
 * @brief LED event handler.
 */
static bool _led_event_handler(app_led_event_id_t event_id)
{
    switch (event_id) {
        case APP_LED_EVENT_ID_ON: {
            ESP_LOGI(LOG_TAG, "APP_LED_EVENT_ID_ON");
            gpio_set_level(LED_PIN, LED_ON);
        } break;

        case APP_LED_EVENT_ID_OFF: {
            ESP_LOGI(LOG_TAG, "APP_LED_EVENT_ID_OFF");
            gpio_set_level(LED_PIN, LED_OFF);
        } break;
    }

    return true;
}

/**
 * @brief System event handler.
 */
static bool _event_handler(core_event_group_t event_group, int event_id)
{
    bool ret = false;

    switch (event_group) {
        case GLAZE_EVENT_GROUP_LED: {
            ESP_LOGI(LOG_TAG, "GLAZE_EVENT_GROUP_LED");
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

void app_led_init()
{
    ESP_LOGI(LOG_TAG, "initializing app...");

    app_main_activity_register(_event_handler);

    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN, LED_OFF);

    ESP_LOGI(LOG_TAG, "initializing app... ok");
}
