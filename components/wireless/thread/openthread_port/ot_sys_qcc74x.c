#include <stdio.h>

#include CHIP_HDR
#include CHIP_GLB_HDR
#include CHIP_SYS_HDR
#include <qcc74x_sec_trng.h>

#include <qcc74x_sys.h>

#include <openthread_port.h>

#include <openthread/platform/memory.h>
#include <openthread/platform/entropy.h>
#include <openthread/platform/misc.h>


void otPlatReset(otInstance *aInstance) 
{
    qcc74x_sys_reset_system();
}

otPlatResetReason otPlatGetResetReason(otInstance *aInstance)
{
    QCC74x_RST_REASON_E rstinfo = qcc74x_sys_rstinfo_get();

    switch (rstinfo) {
        case QCC74x_RST_HARDWARE_WATCHDOG:
        return OT_PLAT_RESET_REASON_WATCHDOG;
        case QCC74x_RST_BOD:
        return OT_PLAT_RESET_REASON_OTHER;
        case QCC74x_RST_HBN:
        return OT_PLAT_RESET_REASON_EXTERNAL;
        case QCC74x_RST_POWER_OFF:
        return OT_PLAT_RESET_REASON_EXTERNAL;
        case QCC74x_RST_SOFTWARE:
        return OT_PLAT_RESET_REASON_SOFTWARE;
        default:
        return OT_PLAT_RESET_REASON_UNKNOWN;
    }

    return OT_PLAT_RESET_REASON_UNKNOWN;
}

void otPlatAssertFail(const char *aFilename, int aLineNumber)
{
    printf("otPlatAssertFail, %s @ %d\r\n", aFilename, aLineNumber);
    configASSERT(false);
}

void otPlatWakeHost(void)
{}

otError otPlatSetMcuPowerState(otInstance *aInstance, otPlatMcuPowerState aState)
{
    return OT_ERROR_NONE;
}
otPlatMcuPowerState otPlatGetMcuPowerState(otInstance *aInstance)
{
    return OT_PLAT_MCU_POWER_STATE_ON;
}

void *otPlatCAlloc(size_t aNum, size_t aSize)
{
    return calloc(aNum, aSize);
}

void otPlatFree(void *aPtr)
{
    free(aPtr);
}

otError otPlatEntropyGet(uint8_t *aOutput, uint16_t aOutputLength) 
{
    qcc74x_trng_readlen(aOutput, aOutputLength);
    return OT_ERROR_NONE;
}
