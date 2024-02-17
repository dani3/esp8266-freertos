/**
 * @file app_main_activity.c
 * @author Daniel Mancebo (daniel.m.aldea@hotmail.com)
 *
 * @brief
 */

#include "app_main_activity.h"

#include "FreeRTOS.h"
#include "task.h"

#include "esp_err.h"
#include "esp_log.h"

// * ----------------------------------------------------------------------------------------------
// * Typedefs and defines
// * ----------------------------------------------------------------------------------------------

#define LOG_TAG "APP_MAIN_ACTIVITY"

#define MAX_NUM_SUBSCRIBERS 32

// * ----------------------------------------------------------------------------------------------
// * Private Functions Prototypes
// * ----------------------------------------------------------------------------------------------

// * ----------------------------------------------------------------------------------------------
// * Private Variables
// * ----------------------------------------------------------------------------------------------

static app_activity_handler_t _subscribers[MAX_NUM_SUBSCRIBERS] = { NULL };

// * ----------------------------------------------------------------------------------------------
// * Private Functions
// * ----------------------------------------------------------------------------------------------

// * ----------------------------------------------------------------------------------------------
// * Public Functions
// * ----------------------------------------------------------------------------------------------

void app_main_activity_start(void* params) {
    ESP_LOGI(LOG_TAG, "Starting %s", __FUNCTION__);
    for (;;) {
        ESP_LOGI(LOG_TAG, "Running...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main_activity_register(app_activity_handler_t handler) {
    ESP_ERROR_CHECK(handler != NULL);

    for (int i = 0; i < MAX_NUM_SUBSCRIBERS; ++i) {
        if (_subscribers[i] != NULL) {
            _subscribers[i] = handler;
        }
    }
}
