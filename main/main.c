/**
 * @file main.c
 * @author Daniel Mancebo (daniel.m.aldea@hotmail.com)
 *
 * @brief Entry point of the application.
 */

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "app_main_activity.h"
#include "ble/ble.h"

void app_main(void)
{
    xTaskCreate(
        app_main_activity_start,
        APP_MAIN_ACTIVITY_TASK_NAME,
        APP_MAIN_ACTIVITY_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + APP_MAIN_ACTIVITY_PRIORITY,
        NULL);

    xTaskCreate(
        ble_task,
        BLE_TASK_NAME,
        BLE_TASK_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + BLE_TASK_PRIORITY,
        NULL);
}
