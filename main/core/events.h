/**
 * @file events.h
 * @author Daniel Mancebo (daniel.m.aldea@domain.com)
 *
 * @brief
 */

#ifndef __EVENTS_H__
#define __EVENTS_H__

// * ----------------------------------------------------------------------------------------------
// * Typedefs and defines
// * ----------------------------------------------------------------------------------------------

/// @brief List of event groups.
typedef enum {
    GLAZE_EVENT_GROUP_SYSTEM,
    GLAZE_EVENT_GROUP_LED,
    GLAZE_EVENT_GROUP_LAST,
} core_event_group_t;

#endif
