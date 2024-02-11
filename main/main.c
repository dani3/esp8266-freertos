/**
 * @file main.c
 *
 * @brief
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include <stdio.h>

void app_main(void)
{
    ESP_LOGI("app_main", "Starting...");

    while (1)
    {
        ESP_LOGI("app_main", "Starting...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
