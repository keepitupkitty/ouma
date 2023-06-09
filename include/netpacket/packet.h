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

#ifndef _NETPACKET_PACKET_H_
#define _NETPACKET_PACKET_H_

struct sockaddr_ll {
  unsigned short int sll_family;
  unsigned short int sll_protocol;
  int sll_ifindex;
  unsigned short int sll_hatype;
  unsigned char sll_pkttype;
  unsigned char sll_halen;
  unsigned char sll_addr[8];
};

/* Packet types.  */

#define PACKET_HOST 0      /* To us.  */
#define PACKET_BROADCAST 1 /* To all.  */
#define PACKET_MULTICAST 2 /* To group.  */
#define PACKET_OTHERHOST 3 /* To someone else.  */
#define PACKET_OUTGOING 4  /* Originated by us . */
#define PACKET_LOOPBACK 5
#define PACKET_FASTROUTE 6

/* Packet socket options.  */

#define PACKET_ADD_MEMBERSHIP 1
#define PACKET_DROP_MEMBERSHIP 2
#define PACKET_RECV_OUTPUT 3
#define PACKET_RX_RING 5
#define PACKET_STATISTICS 6
#define PACKET_COPY_THRESH 7
#define PACKET_AUXDATA 8
#define PACKET_ORIGDEV 9
#define PACKET_VERSION 10
#define PACKET_HDRLEN 11
#define PACKET_RESERVE 12
#define PACKET_TX_RING 13
#define PACKET_LOSS 14
#define PACKET_VNET_HDR 15
#define PACKET_TX_TIMESTAMP 16
#define PACKET_TIMESTAMP 17
#define PACKET_FANOUT 18
#define PACKET_TX_HAS_OFF 19
#define PACKET_QDISC_BYPASS 20
#define PACKET_ROLLOVER_STATS 21
#define PACKET_FANOUT_DATA 22
#define PACKET_IGNORE_OUTGOING 23

struct packet_mreq {
  int mr_ifindex;
  unsigned short int mr_type;
  unsigned short int mr_alen;
  unsigned char mr_address[8];
};

#define PACKET_MR_MULTICAST 0
#define PACKET_MR_PROMISC 1
#define PACKET_MR_ALLMULTI 2
#define PACKET_MR_UNICAST 3

#endif /* !_NETPACKET_PACKET_H_ */
