#ifndef REG_ACCESS_H_
#define REG_ACCESS_H_

/**
 ****************************************************************************************
 * @defgroup REG REG
 * @ingroup PLATFORM_DRIVERS
 *
 * @brief Basic primitives for register access.
 *
 * @{
 ****************************************************************************************
 */
#include "co_utils.h"

/*
 * MACROS
 ****************************************************************************************
 */
#if WL_NIC
#ifndef CHAR_LEN
/// Length of a char in bytes
#define CHAR_LEN    (CHAR_BIT/8)
#endif
/// Macro to read a platform register
#define REG_PL_RD(addr)              (*(volatile uint32_t *)(((void *)(((uint32_t)(addr)) / CHAR_LEN))))

/// Macro to write a platform register
#define REG_PL_WR(addr, value)       (*(volatile uint32_t *)(((void *)(((uint32_t)(addr)) / CHAR_LEN)))) = (value)


/// Macro to read a common ip register
#define REG_IP_RD(addr)              (*(volatile uint32_t *)(addr))

/// Macro to write a common ip register
#define REG_IP_WR(addr, value)       (*(volatile uint32_t *)(addr)) = (value)

/// Macro to read a BLE register
#define REG_BLE_RD(addr)             (*(volatile uint32_t *)(addr))

/// Macro to write a BLE register
#define REG_BLE_WR(addr, value)      (*(volatile uint32_t *)(addr)) = (value)

/// Macro to read a BLE control structure field (16-bit wide)
#define EM_BLE_RD(addr)              (*(volatile uint16_t *)(addr))

/// Macro to write a BLE control structure field (16-bit wide)
#define EM_BLE_WR(addr, value)       (*(volatile uint16_t *)(addr)) = (value)

/// Macro to read a BT register
#define REG_BT_RD(addr)              (*(volatile uint32_t *)(addr))

/// Macro to write a BT register
#define REG_BT_WR(addr, value)       (*(volatile uint32_t *)(addr)) = (value)

/// Macro to read a BT control structure field (16-bit wide)
#define EM_BT_RD(addr)               (*(volatile uint16_t *)(addr))

/// Macro to write a BT control structure field (16-bit wide)
#define EM_BT_WR(addr, value)        (*(volatile uint16_t *)(addr)) = (value)

/// Macro to read a EM field (16-bit wide)
#define EM_RD(addr)               (*(volatile uint16_t *)(addr))

/// Macro to write a EM field (16-bit wide)
#define EM_WR(addr, value)        (*(volatile uint16_t *)(addr)) = (value)

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

#if (defined(CFG_BLE_EMB) || defined(CFG_BT_EMB))
#include "co_utils.h"
#include "em_map.h"       // EM Map

/// retrieve EM address from system address
__INLINE uint16_t em_addr_get(void *sys_addr)
{
    return ((uint16_t) (((uint32_t) sys_addr) - EM_BASE_ADDR));
}

/// Read bytes from EM
__INLINE void em_rd(void *sys_addr, uint16_t em_addr, uint16_t len)
{
    memcpy(sys_addr, (void *)(em_addr + EM_BASE_ADDR), len);
}
/// Write bytes to EM
__INLINE void em_wr(void const *sys_addr, uint16_t em_addr, uint16_t len)
{
    memcpy((void *)(em_addr + EM_BASE_ADDR), sys_addr, len);
}

// copy two exchange memory area
__INLINE void em_cpy(uint16_t dst_em_addr, uint16_t src_em_addr, uint16_t len)
{
    memcpy((void *)(dst_em_addr + EM_BASE_ADDR), (void *)(src_em_addr + EM_BASE_ADDR), len);
}

/// Fill an EM space with the same value
__INLINE void em_set(int value, uint16_t em_addr, uint16_t len)
{
    memset((void *)(em_addr + EM_BASE_ADDR), value, len);
}

/// Read 32-bits value from EM
__INLINE uint32_t em_rd32p(uint16_t em_addr)
{
    return co_read32p((uint32_t)(em_addr + EM_BASE_ADDR));
}
/// Write 32-bits value to EM
__INLINE void em_wr32p(uint16_t em_addr, uint32_t value)
{
    co_write32p((uint32_t)(em_addr + EM_BASE_ADDR), value);
}

/// Read 24-bits value from EM
__INLINE uint32_t em_rd24p(uint16_t em_addr)
{
    return co_read24p((uint32_t)(em_addr + EM_BASE_ADDR));
}
/// Write 24-bits value to EM
__INLINE void em_wr24p(uint16_t em_addr, uint32_t value)
{
    co_write24p((uint32_t)(em_addr + EM_BASE_ADDR), value);
}

/// Read 16-bits value from EM
__INLINE uint16_t em_rd16p(uint16_t em_addr)
{
    return co_read16p((uint32_t)(em_addr + EM_BASE_ADDR));
}
/// Write 16-bits value to EM
__INLINE void em_wr16p(uint16_t em_addr, uint16_t value)
{
    co_write16p((uint32_t)(em_addr + EM_BASE_ADDR), value);
}

/// Read 8-bits value from EM
__INLINE uint8_t em_rd8p(uint16_t em_addr)
{
    return *((uint8_t *)(em_addr + EM_BASE_ADDR));
}
/// Write 8-bits value to EM
__INLINE void em_wr8p(uint16_t em_addr, uint8_t value)
{
    *(uint8_t *)(em_addr + EM_BASE_ADDR) = value;
}
#endif // (defined(CFG_BLE_EMB) || defined(CFG_BT_EMB))
#else
/// Macro to read a platform register
#define REG_PL_RD(addr)              (*(volatile uint32_t *)(HW2CPU(addr)))

/// Macro to write a platform register
#define REG_PL_WR(addr, value)       (*(volatile uint32_t *)(HW2CPU(addr))) = (value)
#endif


/// @} REG

#endif // REG_ACCESS_H_
