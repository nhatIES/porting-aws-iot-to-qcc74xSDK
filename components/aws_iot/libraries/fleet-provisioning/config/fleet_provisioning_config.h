#ifndef FLEET_PROVISIONING_CONFIG_H
#define FLEET_PROVISIONING_CONFIG_H

/**************************************************/
/******* DO NOT CHANGE the following order ********/
/**************************************************/

/* Logging config definition and header files inclusion are required in the following order:
 * 1. Include the header file "logging_levels.h".
 * 2. Define the LIBRARY_LOG_NAME and LIBRARY_LOG_LEVEL macros depending on
 * the logging configuration for Fleet Provisioning.
 * 3. Include the header file "logging_stack.h", if logging is enabled for Fleet Provisioning.
 */

#include "logging_levels.h"

/* Logging configuration for the Fleet Provisioning library. */
#ifndef LIBRARY_LOG_NAME
    #define LIBRARY_LOG_NAME    "FleetProvisioning"
#endif

#ifndef LIBRARY_LOG_LEVEL
    #define LIBRARY_LOG_LEVEL    LOG_INFO
#endif

#include "logging_stack.h"

/************ End of logging configuration ****************/

#endif /* FLEET_PROVISIONING_CONFIG_H */