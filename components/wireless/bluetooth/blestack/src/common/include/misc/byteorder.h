/** @file
 *  @brief Byte order helpers.
 */

/*
 * Copyright (c) 2015-2016, Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __BYTEORDER_H__
#define __BYTEORDER_H__

#include <zephyr/types.h>
#include <stddef.h>
#include <misc/__assert.h>

#ifndef __BYTE_ORDER__
#define __BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__
#endif


/* Internal helpers only used by the sys_* APIs further below */
#define __bswap_16(x) ((u16_t) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)))
#define __bswap_32(x) ((u32_t) ((((x) >> 24) & 0xff) | \
				   (((x) >> 8) & 0xff00) | \
				   (((x) & 0xff00) << 8) | \
				   (((x) & 0xff) << 24)))
#define __bswap_64(x) ((u64_t) ((((x) >> 56) & 0xff) | \
				   (((x) >> 40) & 0xff00) | \
				   (((x) >> 24) & 0xff0000) | \
				   (((x) >> 8) & 0xff000000) | \
				   (((x) & 0xff000000) << 8) | \
				   (((x) & 0xff0000) << 24) | \
				   (((x) & 0xff00) << 40) | \
				   (((x) & 0xff) << 56)))

/** @def sys_le16_to_cpu
 *  @brief Convert 16-bit integer from little-endian to host endianness.
 *
 *  @param val 16-bit integer in little-endian format.
 *
 *  @return 16-bit integer in host endianness.
 */

/** @def sys_cpu_to_le16
 *  @brief Convert 16-bit integer from host endianness to little-endian.
 *
 *  @param val 16-bit integer in host endianness.
 *
 *  @return 16-bit integer in little-endian format.
 */

/** @def sys_be16_to_cpu
 *  @brief Convert 16-bit integer from big-endian to host endianness.
 *
 *  @param val 16-bit integer in big-endian format.
 *
 *  @return 16-bit integer in host endianness.
 */

/** @def sys_cpu_to_be16
 *  @brief Convert 16-bit integer from host endianness to big-endian.
 *
 *  @param val 16-bit integer in host endianness.
 *
 *  @return 16-bit integer in big-endian format.
 */

/** @def sys_le32_to_cpu
 *  @brief Convert 32-bit integer from little-endian to host endianness.
 *
 *  @param val 32-bit integer in little-endian format.
 *
 *  @return 32-bit integer in host endianness.
 */

/** @def sys_cpu_to_le32
 *  @brief Convert 32-bit integer from host endianness to little-endian.
 *
 *  @param val 32-bit integer in host endianness.
 *
 *  @return 32-bit integer in little-endian format.
 */

/** @def sys_be32_to_cpu
 *  @brief Convert 32-bit integer from big-endian to host endianness.
 *
 *  @param val 32-bit integer in big-endian format.
 *
 *  @return 32-bit integer in host endianness.
 */

/** @def sys_cpu_to_be32
 *  @brief Convert 32-bit integer from host endianness to big-endian.
 *
 *  @param val 32-bit integer in host endianness.
 *
 *  @return 32-bit integer in big-endian format.
 */

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define sys_le16_to_cpu(val) (val)
#define sys_cpu_to_le16(val) (val)
#define sys_be16_to_cpu(val) __bswap_16(val)
#define sys_cpu_to_be16(val) __bswap_16(val)
#define sys_le32_to_cpu(val) (val)
#define sys_cpu_to_le32(val) (val)
#define sys_le64_to_cpu(val) (val)
#define sys_cpu_to_le64(val) (val)
#define sys_be32_to_cpu(val) __bswap_32(val)
#define sys_cpu_to_be32(val) __bswap_32(val)
#define sys_be64_to_cpu(val) __bswap_64(val)
#define sys_cpu_to_be64(val) __bswap_64(val)
/********************************************************************************
** Macros to get and put bytes to a stream (Little Endian format).
*/
#define UINT32_TO_STREAM(p, u32) {*(p)++ = (u8_t)(u32); *(p)++ = (u8_t)((u32) >> 8); *(p)++ = (u8_t)((u32) >> 16); *(p)++ = (u8_t)((u32) >> 24);}
#define UINT24_TO_STREAM(p, u24) {*(p)++ = (u8_t)(u24); *(p)++ = (u8_t)((u24) >> 8); *(p)++ = (u8_t)((u24) >> 16);}
#define UINT16_TO_STREAM(p, u16) {*(p)++ = (u8_t)(u16); *(p)++ = (u8_t)((u16) >> 8);}
#define UINT8_TO_STREAM(p, u8)   {*(p)++ = (u8_t)(u8);}

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define sys_le16_to_cpu(val) __bswap_16(val)
#define sys_cpu_to_le16(val) __bswap_16(val)
#define sys_be16_to_cpu(val) (val)
#define sys_cpu_to_be16(val) (val)
#define sys_le32_to_cpu(val) __bswap_32(val)
#define sys_cpu_to_le32(val) __bswap_32(val)
#define sys_le64_to_cpu(val) __bswap_64(val)
#define sys_cpu_to_le64(val) __bswap_64(val)
#define sys_be32_to_cpu(val) (val)
#define sys_cpu_to_be32(val) (val)
#define sys_be64_to_cpu(val) (val)
#define sys_cpu_to_be64(val) (val)
/********************************************************************************
** Macros to get and put bytes to a stream (Big Endian format)
*/
#define UINT32_TO_STREAM(p, u32) {*(p)++ = (u8_t)((u32) >> 24);  *(p)++ = (u8_t)((u32) >> 16); *(p)++ = (u8_t)((u32) >> 8); *(p)++ = (u8_t)(u32); }
#define UINT24_TO_STREAM(p, u24) {*(p)++ = (u8_t)((u24) >> 16); *(p)++ = (u8_t)((u24) >> 8); *(p)++ = (u8_t)(u24);}
#define UINT16_TO_STREAM(p, u16) {*(p)++ = (u8_t)((u16) >> 8); *(p)++ = (u8_t)(u16);}
#define UINT8_TO_STREAM(p, u8)   {*(p)++ = (u8_t)(u8);}

#else
#error "Unknown byte order"
#endif

/**
 *  @brief Put a 16-bit integer as big-endian to arbitrary location.
 *
 *  Put a 16-bit integer, originally in host endianness, to a
 *  potentially unaligned memory location in big-endian format.
 *
 *  @param val 16-bit integer in host endianness.
 *  @param dst Destination memory address to store the result.
 */
static inline void sys_put_be16(u16_t val, u8_t dst[2])
{
	dst[0] = val >> 8;
	dst[1] = val;
}

/**
 *  @brief Put a 24-bit integer as big-endian to arbitrary location.
 *
 *  Put a 24-bit integer, originally in host endianness, to a
 *  potentially unaligned memory location in big-endian format.
 *
 *  @param val 24-bit integer in host endianness.
 *  @param dst Destination memory address to store the result.
 */
static inline void sys_put_be24(uint32_t val, uint8_t dst[3])
{
	dst[0] = val >> 16;
	sys_put_be16(val, &dst[1]);
}

/**
 *  @brief Put a 32-bit integer as big-endian to arbitrary location.
 *
 *  Put a 32-bit integer, originally in host endianness, to a
 *  potentially unaligned memory location in big-endian format.
 *
 *  @param val 32-bit integer in host endianness.
 *  @param dst Destination memory address to store the result.
 */
static inline void sys_put_be32(u32_t val, u8_t dst[4])
{
	sys_put_be16(val >> 16, dst);
	sys_put_be16(val, &dst[2]);
}

/**
 *  @brief Put a 64-bit integer as big-endian to arbitrary location.
 *
 *  Put a 64-bit integer, originally in host endianness, to a
 *  potentially unaligned memory location in big-endian format.
 *
 *  @param val 64-bit integer in host endianness.
 *  @param dst Destination memory address to store the result.
 */
static inline void sys_put_be64(uint64_t val, uint8_t dst[8])
{
	sys_put_be32(val >> 32, dst);
	sys_put_be32(val, &dst[4]);
}

/**
 *  @brief Put a 16-bit integer as little-endian to arbitrary location.
 *
 *  Put a 16-bit integer, originally in host endianness, to a
 *  potentially unaligned memory location in little-endian format.
 *
 *  @param val 16-bit integer in host endianness.
 *  @param dst Destination memory address to store the result.
 */
static inline void sys_put_le16(u16_t val, u8_t dst[2])
{
	dst[0] = val;
	dst[1] = val >> 8;
}

/**
 *  @brief Put a 24-bit integer as little-endian to arbitrary location.
 *
 *  Put a 24-bit integer, originally in host endianness, to a
 *  potentially unaligned memory location in littel-endian format.
 *
 *  @param val 24-bit integer in host endianness.
 *  @param dst Destination memory address to store the result.
 */
static inline void sys_put_le24(uint32_t val, uint8_t dst[3])
{
	sys_put_le16(val, dst);
	dst[2] = val >> 16;
}

/**
 *  @brief Put a 32-bit integer as little-endian to arbitrary location.
 *
 *  Put a 32-bit integer, originally in host endianness, to a
 *  potentially unaligned memory location in little-endian format.
 *
 *  @param val 32-bit integer in host endianness.
 *  @param dst Destination memory address to store the result.
 */
static inline void sys_put_le32(u32_t val, u8_t dst[4])
{
	sys_put_le16(val, dst);
	sys_put_le16(val >> 16, &dst[2]);
}

/**
 *  @brief Put a 64-bit integer as little-endian to arbitrary location.
 *
 *  Put a 64-bit integer, originally in host endianness, to a
 *  potentially unaligned memory location in little-endian format.
 *
 *  @param val 64-bit integer in host endianness.
 *  @param dst Destination memory address to store the result.
 */
static inline void sys_put_le64(u64_t val, u8_t dst[8])
{
	sys_put_le32(val, dst);
	sys_put_le32(val >> 32, &dst[4]);
}

/**
 *  @brief Get a 16-bit integer stored in big-endian format.
 *
 *  Get a 16-bit integer, stored in big-endian format in a potentially
 *  unaligned memory location, and convert it to the host endianness.
 *
 *  @param src Location of the big-endian 16-bit integer to get.
 *
 *  @return 16-bit integer in host endianness.
 */
static inline u16_t sys_get_be16(const u8_t src[2])
{
	return ((u16_t)src[0] << 8) | src[1];
}

/**
 *  @brief Get a 24-bit integer stored in big-endian format.
 *
 *  Get a 24-bit integer, stored in big-endian format in a potentially
 *  unaligned memory location, and convert it to the host endianness.
 *
 *  @param src Location of the big-endian 24-bit integer to get.
 *
 *  @return 24-bit integer in host endianness.
 */
static inline uint32_t sys_get_be24(const uint8_t src[3])
{
	return ((uint32_t)src[0] << 16) | sys_get_be16(&src[1]);
}

/**
 *  @brief Get a 32-bit integer stored in big-endian format.
 *
 *  Get a 32-bit integer, stored in big-endian format in a potentially
 *  unaligned memory location, and convert it to the host endianness.
 *
 *  @param src Location of the big-endian 32-bit integer to get.
 *
 *  @return 32-bit integer in host endianness.
 */
static inline u32_t sys_get_be32(const u8_t src[4])
{
	return ((u32_t)sys_get_be16(&src[0]) << 16) | sys_get_be16(&src[2]);
}

/**
 *  @brief Get a 16-bit integer stored in little-endian format.
 *
 *  Get a 16-bit integer, stored in little-endian format in a potentially
 *  unaligned memory location, and convert it to the host endianness.
 *
 *  @param src Location of the little-endian 16-bit integer to get.
 *
 *  @return 16-bit integer in host endianness.
 */
static inline u16_t sys_get_le16(const u8_t src[2])
{
	return ((u16_t)src[1] << 8) | src[0];
}

/**
 *  @brief Get a 24-bit integer stored in big-endian format.
 *
 *  Get a 24-bit integer, stored in big-endian format in a potentially
 *  unaligned memory location, and convert it to the host endianness.
 *
 *  @param src Location of the big-endian 24-bit integer to get.
 *
 *  @return 24-bit integer in host endianness.
 */
static inline uint32_t sys_get_le24(const uint8_t src[3])
{
	return ((uint32_t)src[2] << 16) | sys_get_le16(&src[0]);
}

/**
 *  @brief Get a 32-bit integer stored in little-endian format.
 *
 *  Get a 32-bit integer, stored in little-endian format in a potentially
 *  unaligned memory location, and convert it to the host endianness.
 *
 *  @param src Location of the little-endian 32-bit integer to get.
 *
 *  @return 32-bit integer in host endianness.
 */
static inline u32_t sys_get_le32(const u8_t src[4])
{
	return ((u32_t)sys_get_le16(&src[2]) << 16) | sys_get_le16(&src[0]);
}

/**
 *  @brief Get a 64-bit integer stored in little-endian format.
 *
 *  Get a 64-bit integer, stored in little-endian format in a potentially
 *  unaligned memory location, and convert it to the host endianness.
 *
 *  @param src Location of the little-endian 64-bit integer to get.
 *
 *  @return 64-bit integer in host endianness.
 */
static inline u64_t sys_get_le64(const u8_t src[8])
{
	return ((u64_t)sys_get_le32(&src[4]) << 32) | sys_get_le32(&src[0]);
}

/**
 * @brief Swap one buffer content into another
 *
 * Copy the content of src buffer into dst buffer in reversed order,
 * i.e.: src[n] will be put in dst[end-n]
 * Where n is an index and 'end' the last index in both arrays.
 * The 2 memory pointers must be pointing to different areas, and have
 * a minimum size of given length.
 *
 * @param dst A valid pointer on a memory area where to copy the data in
 * @param src A valid pointer on a memory area where to copy the data from
 * @param length Size of both dst and src memory areas
 */
#if defined(QCC74x_BLE)
static inline void sys_memcpy_swap(void *dst, const void *src, size_t length)
{
	u8_t *pdst = (u8_t *)dst;
	const u8_t *psrc = (const u8_t *)src;

	__ASSERT(((psrc < pdst && (psrc + length) <= pdst) ||
		  (psrc > pdst && (pdst + length) <= psrc)),
		 "Source and destination buffers must not overlap");

	psrc += length - 1;

	for (; length > 0; length--) {
		*pdst++ = *psrc--;
	}
}
#else
static inline void sys_memcpy_swap(void *dst, const void *src, size_t length)
{
	__ASSERT(((src < dst && (src + length) <= dst) ||
		  (src > dst && (dst + length) <= src)),
		 "Source and destination buffers must not overlap");

	src += length - 1;

	for (; length > 0; length--) {
		*((u8_t *)dst++) = *((u8_t *)src--);
	}
}
#endif
/**
 * @brief Swap buffer content
 *
 * In-place memory swap, where final content will be reversed.
 * I.e.: buf[n] will be put in buf[end-n]
 * Where n is an index and 'end' the last index of buf.
 *
 * @param buf A valid pointer on a memory area to swap
 * @param length Size of buf memory area
 */
static inline void sys_mem_swap(void *buf, size_t length)
{
	size_t i;

	for (i = 0; i < (length/2); i++) {
		u8_t tmp = ((u8_t *)buf)[i];

		((u8_t *)buf)[i] = ((u8_t *)buf)[length - 1 - i];
		((u8_t *)buf)[length - 1 - i] = tmp;
	}
}

#endif /* __BYTEORDER_H__ */
