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
#define APP_MAIN_ACTIVITY_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)
#define APP_MAIN_ACTIVITY_PRIORITY   1

/// @brief Function pointer that an activity can use to register itself as a system event
/// subscriber.
typedef bool (*app_activity_handler_t)(core_event_group_t event_group, int event_id);

/// @brief Enum that represents the event ids within the `CORE_EVENT_GROUP_SYSTEM` group.
typedef enum {
    CORE_EVENT_ON_CREATE = 0,
    CORE_EVENT_LAST,
} core_event_id_t;

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

/**
 * @brief Send an event to the system.
 *
 * @param event_group group this event belongs to.
 * @param event_id group id.
 * @param delay_ms time in milliseconds the sending of the event needs to be delayed by.
 */
void app_main_activity_send_event(core_event_group_t event_group, int event_id, int delay_ms);

#endif
