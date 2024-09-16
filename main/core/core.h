/**
 * @file core.h
 * @author Daniel Mancebo (daniel.m.aldea@domain.com)
 *
 * @brief Implementation of core functionality shared across the project.
 */

#ifndef __CORE_H__
#define __CORE_H__

// * ----------------------------------------------------------------------------------------------
// * Includes
// * ----------------------------------------------------------------------------------------------

#include <assert.h>

#include "esp_log.h"

// * ----------------------------------------------------------------------------------------------
// * Typedefs and defines
// * ----------------------------------------------------------------------------------------------

#define CORE_ASSERT(x)                                                                             \
    do {                                                                                           \
        if (!(x)) {                                                                                \
            ESP_LOGE("CORE", "Module '%s' panicked in %s:%d", __FILE__, __FUNCTION__, __LINE__);   \
            assert(false);                                                                         \
        }                                                                                          \
    } while (true)

// * ----------------------------------------------------------------------------------------------
// * Public API
// * ----------------------------------------------------------------------------------------------

/**
 * @brief Get the current timestamp in milliseconds.
 *
 * @return current timestamp in milliseconds.
 */
int core_get_timestamp_ms(void);

#endif
