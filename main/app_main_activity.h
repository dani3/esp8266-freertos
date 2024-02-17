/**
 * @file app_main_activity.h
 * @author Daniel Mancebo (daniel.m.aldea@hotmail.com)
 *
 * @brief
 */

#ifndef __APP_MAIN_ACTIVITY_H__
#define __APP_MAIN_ACTIVITY_H__

#include "FreeRTOSConfig.h"

#include "core/events.h"

#include <stdint.h>

// * ----------------------------------------------------------------------------------------------
// * Typedefs and defines
// * ----------------------------------------------------------------------------------------------

#define APP_MAIN_ACTIVITY_TASK_NAME  "APP_MAIN_ACTIVITY"
#define APP_MAIN_ACTIVITY_STACK_SIZE configMINIMAL_STACK_SIZE
#define APP_MAIN_ACTIVITY_PRIORITY   1

/// @brief Function pointer that an activity can use to register itself as a system event
/// subscriber.
typedef void (*app_activity_handler_t)(core_event_group_t event_group, size_t event_id);

// * ----------------------------------------------------------------------------------------------
// * Public API
// * ----------------------------------------------------------------------------------------------

/**
 * @brief Start the main activity task.
 */
void app_main_activity_start(void *params);

/**
 * @brief Register a new activity handler.
 *
 * @param handler function pointer of type `app_activity_handler_t`.
 */
void app_main_activity_register(app_activity_handler_t handler);

#endif
