/**
 * @file ble.c
 * @author Daniel Mancebo (daniel.m.aldea@hotmail.com)
 *
 * @brief Implementation of the task that handles the BLE communications.
 */

#include "FreeRTOS.h"
#include "projdefs.h"
#include "task.h"

#include "string.h"

#include "driver/uart.h"
#include "esp_log.h"

#include "ble.h"

// * ----------------------------------------------------------------------------------------------
// * Typedefs and defines
// * ----------------------------------------------------------------------------------------------

#define LOG_TAG "BLE_TASK"

#define UART_NUM UART_NUM_0
#define BUF_SIZE 1024

// * ----------------------------------------------------------------------------------------------
// * Private Functions Prototypes
// * ----------------------------------------------------------------------------------------------

static void _init(void);

// * ----------------------------------------------------------------------------------------------
// * Private Variables
// * ----------------------------------------------------------------------------------------------

// * ----------------------------------------------------------------------------------------------
// * Private Functions
// * ----------------------------------------------------------------------------------------------

static void _init(void)
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    uart_param_config(UART_NUM, &uart_config);
    uart_driver_install(UART_NUM, BUF_SIZE, 0, 0, NULL, 0);
}

static void _read_from_ic(void)
{
    uint8_t data[BUF_SIZE];
    int len = uart_read_bytes(UART_NUM, data, BUF_SIZE - 1, 1000 / portTICK_PERIOD_MS);
    if (len > 0) {
        data[len] = '\0'; // Null-terminate the response
        printf("Received: %s\n", data);
    }
}

// * ----------------------------------------------------------------------------------------------
// * Public Functions
// * ----------------------------------------------------------------------------------------------

void ble_task(void* parameters)
{
    ESP_LOGI(LOG_TAG, "initializing activity...");
    _init();
    ESP_LOGI(LOG_TAG, "initializing activity... ok");

    const char* cmd = "AT\r\n";
    for (;;) {
        uart_write_bytes(UART_NUM, cmd, strlen(cmd));
        _read_from_ic();
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    vTaskDelete(NULL);
}
