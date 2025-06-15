// Copyright 2021 Espressif Systems (Shanghai) CO LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License

/* Platform clock include. */
#include "clock.h"

#include "FreeRTOS.h"
#include "task.h"
#include <sys/time.h>

uint32_t Clock_GetTimeMs( void )
{
    /* QCC74x: Use FreeRTOS tick count for time in milliseconds */
    TickType_t ticks = xTaskGetTickCount();
    
    /* Convert ticks to milliseconds using configTICK_RATE_HZ */
    uint32_t timeMs = (uint32_t)(ticks * 1000UL / configTICK_RATE_HZ);

    /* Libraries need only the lower 32 bits of the time in milliseconds, since
     * this function is used only for calculating the time difference.
     * Also, the possible overflows of this time value are handled by the
     * libraries. */
    return timeMs;
}

/*-----------------------------------------------------------*/

void Clock_SleepMs( uint32_t sleepTimeMs )
{
    /* QCC74x: Use FreeRTOS vTaskDelay with pdMS_TO_TICKS conversion */
    vTaskDelay( pdMS_TO_TICKS(sleepTimeMs) );
}