/**
 * @file ble.h
 * @author Daniel Mancebo (daniel.m.aldea@hotmail.com)
 *
 * @brief Task that handles BLE communications.
 */

#ifndef __APP_BLE_H__
#define __APP_BLE_H__

// * ----------------------------------------------------------------------------------------------
// * Typedefs and defines
// * ----------------------------------------------------------------------------------------------

#define BLE_TASK_NAME       "BLE_TASK"
#define BLE_TASK_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)
#define BLE_TASK_PRIORITY   1

// * ----------------------------------------------------------------------------------------------
// * Public API
// * ----------------------------------------------------------------------------------------------

/**
 * @brief BLE task function.
 */
void ble_task(void* parameters);

#endif
