/**
 * @file app_led.h
 * @author Daniel Mancebo (daniel.m.aldea@hotmail.com)
 *
 * @brief App that handles the LED.
 */

#ifndef __APP_LED_H__
#define __APP_LED_H__

// * ----------------------------------------------------------------------------------------------
// * Typedefs and defines
// * ----------------------------------------------------------------------------------------------

typedef enum {
    APP_LED_EVENT_ID_ON = 0,
    APP_LED_EVENT_ID_OFF,
} app_led_event_id_t;

// * ----------------------------------------------------------------------------------------------
// * Public API
// * ----------------------------------------------------------------------------------------------

/**
 * @brief Initialize the app.
 */
void app_led_init();

#endif
