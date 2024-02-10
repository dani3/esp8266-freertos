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

    int i = 0;
    while (1)
    {
        printf("[%d] Hello world!\n", i);
        i++;
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
