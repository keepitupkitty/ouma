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

#ifndef _NETINET_UDP_H
#define _NETINET_UDP_H

#include <stdint.h>
#include <sys/types.h>

/* UDP header as specified by RFC 768, August 1980. */

struct udphdr {
  __extension__ union {
    struct {
      uint16_t uh_sport; /* source port */
      uint16_t uh_dport; /* destination port */
      uint16_t uh_ulen;  /* udp length */
      uint16_t uh_sum;   /* udp checksum */
    };
    struct {
      uint16_t source;
      uint16_t dest;
      uint16_t len;
      uint16_t check;
    };
  };
};

/* UDP socket options */
#define UDP_CORK 1 /* Never send partially complete segments.  */
#define UDP_ENCAP                 \
  100 /* Set the socket to accept \
         encapsulated packets.  */
#define UDP_NO_CHECK6_TX                  \
  101 /* Disable sending checksum for UDP \
         over IPv6.  */
#define UDP_NO_CHECK6_RX                                      \
  102                   /* Disable accepting checksum for UDP \
                           over IPv6.  */
#define UDP_SEGMENT 103 /* Set GSO segmentation size.  */
#define UDP_GRO 104     /* This socket can receive UDP GRO packets.  */

/* UDP encapsulation types */
#define UDP_ENCAP_ESPINUDP_NON_IKE 1 /* draft-ietf-ipsec-nat-t-ike-00/01 */
#define UDP_ENCAP_ESPINUDP 2         /* draft-ietf-ipsec-udp-encaps-06 */
#define UDP_ENCAP_L2TPINUDP 3        /* rfc2661 */
#define UDP_ENCAP_GTP0 4             /* GSM TS 09.60 */
#define UDP_ENCAP_GTP1U 5            /* 3GPP TS 29.060 */

#define SOL_UDP 17 /* sockopt level for UDP */

#endif /* !_NETINET_UDP_H */
