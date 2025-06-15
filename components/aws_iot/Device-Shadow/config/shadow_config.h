#ifndef SHADOW_CONFIG_H
#define SHADOW_CONFIG_H

/**************************************************/
/******* DO NOT CHANGE the following order ********/
/**************************************************/

/* Logging config definition and header files inclusion are required in the following order:
 * 1. Include the header file "logging_levels.h".
 * 2. Define the LIBRARY_LOG_NAME and LIBRARY_LOG_LEVEL macros depending on
 * the logging configuration for Device Shadow.
 * 3. Include the header file "logging_stack.h", if logging is enabled for Device Shadow.
 */

#include "logging_levels.h"

/* Logging configuration for the Device Shadow library. */
#ifndef LIBRARY_LOG_NAME
    #define LIBRARY_LOG_NAME    "DeviceShadow"
#endif

#ifndef LIBRARY_LOG_LEVEL
    #define LIBRARY_LOG_LEVEL    LOG_INFO
#endif

#include "logging_stack.h"

/************ End of logging configuration ****************/

#endif /* SHADOW_CONFIG_H */