// Copyright 2024 AWS IoT Device SDK for QCC74x SDK
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

#include "qcc74x_mtimer.h"

uint32_t Clock_GetTimeMs( void )
{
    /* qcc74x_mtimer_get_time_ms returns time in milliseconds */
    uint64_t timeMs = qcc74x_mtimer_get_time_ms();

    /* Libraries need only the lower 32 bits of the time in milliseconds, since
     * this function is used only for calculating the time difference.
     * Also, the possible overflows of this time value are handled by the
     * libraries. */
    return ( uint32_t ) timeMs;
}

/*-----------------------------------------------------------*/

void Clock_SleepMs( uint32_t sleepTimeMs )
{
    qcc74x_mtimer_delay_ms( sleepTimeMs );
}