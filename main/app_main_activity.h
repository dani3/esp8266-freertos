/**
 * @file app_main_activity.h
 * @author Daniel Mancebo (daniel.m.aldea@hotmail.com)
 *
 * @brief
 */

#ifndef __APP_MAIN_ACTIVITY_H__
#define __APP_MAIN_ACTIVITY_H__

#include "FreeRTOSConfig.h"

#define APP_MAIN_ACTIVITY_TASK_NAME  "APP_MAIN_ACTIVITY"
#define APP_MAIN_ACTIVITY_STACK_SIZE configMINIMAL_STACK_SIZE
#define APP_MAIN_ACTIVITY_PRIORITY   1

/**
 * @brief
 */
void app_main_activity_start(void *params);

#endif
