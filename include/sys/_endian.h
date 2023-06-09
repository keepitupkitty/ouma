/*
 * Copyright 2023 rSec Linux
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _SYS__ENDIAN_H_
#define _SYS__ENDIAN_H_

#if !defined(_MACHINE_ENDIAN_H_) && !defined(_BYTESWAP_H_) &&                  \
    !defined(_ENDIAN_H_)
#error "sys/_endian.h should not be included directly"
#endif

/* BSD Compatiblity */
#define _BYTE_ORDER __BYTE_ORDER__

/*
 * Definitions for byte order, according to byte significance from low
 * address to high.
 */
#define _LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__ /* LSB first: 1234 */
#define _BIG_ENDIAN __ORDER_BIG_ENDIAN__       /* MSB first: 4321 */
#define _PDP_ENDIAN                                                            \
  __ORDER_PDP_ENDIAN__ /* LSB first in word,                                   \
                        * MSW first in long: 3412 */

/*
 * Deprecated variants that don't have enough underscores to be useful in more
 * strict namespaces.
 */
#if __BSD_VISIBLE
#define LITTLE_ENDIAN _LITTLE_ENDIAN
#define BIG_ENDIAN _BIG_ENDIAN
#define PDP_ENDIAN _PDP_ENDIAN
#define BYTE_ORDER _BYTE_ORDER
#endif

/* bswap primitives, based on compiler builtins */
#define __bswap16(x) __builtin_bswap16(x)
#define __bswap32(x) __builtin_bswap32(x)
#define __bswap64(x) __builtin_bswap64(x)

#if _BYTE_ORDER == _LITTLE_ENDIAN
#define __ntohl(x) (__bswap32(x))
#define __ntohs(x) (__bswap16(x))
#define __htonl(x) (__bswap32(x))
#define __htons(x) (__bswap16(x))
#elif _BYTE_ORDER == _BIG_ENDIAN
#define __htonl(x) ((__uint32_t)(x))
#define __htons(x) ((__uint16_t)(x))
#define __ntohl(x) ((__uint32_t)(x))
#define __ntohs(x) ((__uint16_t)(x))
#endif

/*
 * Host to big endian, host to little endian, big endian to host, and little
 * endian to host byte order functions as detailed in byteorder(9).
 */
#if _BYTE_ORDER == _LITTLE_ENDIAN
#define htobe16(x) __bswap16((x))
#define htobe32(x) __bswap32((x))
#define htobe64(x) __bswap64((x))
#define htole16(x) ((uint16_t)(x))
#define htole32(x) ((uint32_t)(x))
#define htole64(x) ((uint64_t)(x))

#define be16toh(x) __bswap16((x))
#define be32toh(x) __bswap32((x))
#define be64toh(x) __bswap64((x))
#define le16toh(x) ((uint16_t)(x))
#define le32toh(x) ((uint32_t)(x))
#define le64toh(x) ((uint64_t)(x))
#else /* _BYTE_ORDER != _LITTLE_ENDIAN */
#define htobe16(x) ((uint16_t)(x))
#define htobe32(x) ((uint32_t)(x))
#define htobe64(x) ((uint64_t)(x))
#define htole16(x) __bswap16((x))
#define htole32(x) __bswap32((x))
#define htole64(x) __bswap64((x))

#define be16toh(x) ((uint16_t)(x))
#define be32toh(x) ((uint32_t)(x))
#define be64toh(x) ((uint64_t)(x))
#define le16toh(x) __bswap16((x))
#define le32toh(x) __bswap32((x))
#define le64toh(x) __bswap64((x))
#endif /* _BYTE_ORDER == _LITTLE_ENDIAN */

#endif /* _SYS__ENDIAN_H_ */
