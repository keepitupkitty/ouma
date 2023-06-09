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

#ifndef _NETINET_IF_TR_H_
#define _NETINET_IF_TR_H_

#include <stdint.h>
#include <sys/types.h>

/* IEEE 802.5 Token-Ring magic constants.  The frame sizes omit the preamble
   and FCS/CRC (frame check sequence). */
#define TR_ALEN 6 /* Octets in one token-ring addr */
#define TR_HLEN (sizeof(struct trh_hdr) + sizeof(struct trllc))
#define AC 0x10
#define LLC_FRAME 0x40

/* LLC and SNAP constants */
#define EXTENDED_SAP 0xAA
#define UI_CMD 0x03

/* This is an Token-Ring frame header. */
struct trh_hdr {
  uint8_t ac;             /* access control field */
  uint8_t fc;             /* frame control field */
  uint8_t daddr[TR_ALEN]; /* destination address */
  uint8_t saddr[TR_ALEN]; /* source address */
  uint16_t rcf;           /* route control field */
  uint16_t rseg[8];       /* routing registers */
};

/* This is an Token-Ring LLC structure */
struct trllc {
  uint8_t dsap;       /* destination SAP */
  uint8_t ssap;       /* source SAP */
  uint8_t llc;        /* LLC control field */
  uint8_t protid[3];  /* protocol id */
  uint16_t ethertype; /* ether type field */
};

/* Token-Ring statistics collection data. */
struct tr_statistics {
  unsigned long rx_packets; /* total packets received	*/
  unsigned long tx_packets; /* total packets transmitted	*/
  unsigned long rx_bytes;   /* total bytes received   	*/
  unsigned long tx_bytes;   /* total bytes transmitted	*/
  unsigned long rx_errors;  /* bad packets received		*/
  unsigned long tx_errors;  /* packet transmit problems	*/
  unsigned long rx_dropped; /* no space in linux buffers	*/
  unsigned long tx_dropped; /* no space available in linux	*/
  unsigned long multicast;  /* multicast packets received	*/
  unsigned long transmit_collision;

  /* detailed Token-Ring errors. See IBM Token-Ring Network
     Architecture for more info */

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

/* source routing stuff */
#define TR_RII 0x80
#define TR_RCF_DIR_BIT 0x80
#define TR_RCF_LEN_MASK 0x1f00
#define TR_RCF_BROADCAST 0x8000         /* all-routes broadcast */
#define TR_RCF_LIMITED_BROADCAST 0xC000 /* single-route broadcast */
#define TR_RCF_FRAME2K 0x20
#define TR_RCF_BROADCAST_MASK 0xC000
#define TR_MAXRIFLEN 18

#ifdef _GNU_SOURCE_
struct trn_hdr {
  uint8_t trn_ac;             /* access control field */
  uint8_t trn_fc;             /* field control field */
  uint8_t trn_dhost[TR_ALEN]; /* destination host */
  uint8_t trn_shost[TR_ALEN]; /* source host */
  uint16_t trn_rcf;           /* route control field */
  uint16_t trn_rseg[8];       /* routing registers */
};

#endif /* !_GNU_SOURCE_ */

#endif /* !_NETINET_IF_TR_H_ */
