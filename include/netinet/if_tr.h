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

#ifndef _NETINET_IF_TR_H
#define _NETINET_IF_TR_H

#include <stdint.h>
#include <sys/types.h>

#define TR_ALEN 6
#define TR_HLEN (sizeof(struct trh_hdr) + sizeof(struct trllc))
#define AC 0x10
#define LLC_FRAME 0x40

#define EXTENDED_SAP 0xAA
#define UI_CMD 0x03

struct trh_hdr {
  uint8_t ac;
  uint8_t fc;
  uint8_t daddr[TR_ALEN];
  uint8_t saddr[TR_ALEN];
  uint16_t rcf;
  uint16_t rseg[8];
};

struct trllc {
  uint8_t dsap;
  uint8_t ssap;
  uint8_t llc;
  uint8_t protid[3];
  uint16_t ethertype;
};

struct tr_statistics {
  unsigned long rx_packets;
  unsigned long tx_packets;
  unsigned long rx_bytes;
  unsigned long tx_bytes;
  unsigned long rx_errors;
  unsigned long tx_errors;
  unsigned long rx_dropped unsigned long tx_dropped;
  unsigned long multicast;
  unsigned long transmit_collision;
  unsigned long line_errors;
  unsigned long internal_errors;
  unsigned long burst_errors;
  unsigned long A_C_errors;
  unsigned long abort_delimiters;
  unsigned long lost_frames;
  unsigned long recv_congest_count;
  unsigned long frame_copied_errors;
  unsigned long frequency_errors;
  unsigned long token_errors;
  unsigned long dummy1;
};

#define TR_RII 0x80
#define TR_RCF_DIR_BIT 0x80
#define TR_RCF_LEN_MASK 0x1f00
#define TR_RCF_BROADCAST 0x8000
#define TR_RCF_LIMITED_BROADCAST 0xC000
#define TR_RCF_FRAME2K 0x20
#define TR_RCF_BROADCAST_MASK 0xC000
#define TR_MAXRIFLEN 18

#if defined(__BSD_VISIBLE_)
struct trn_hdr {
  uint8_t trn_ac;
  uint8_t trn_fc;
  uint8_t trn_dhost[TR_ALEN];
  uint8_t trn_shost[TR_ALEN];
  uint16_t trn_rcf;
  uint16_t trn_rseg[8];
};

#endif

#endif /* !_NETINET_IF_TR_H */
