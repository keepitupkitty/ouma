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

#ifndef _NETINET_TCP_H
#define _NETINET_TCP_H

#include <sys/cdefs.h>

#define TCP_NODELAY 1
#define TCP_MAXSEG 2
#define TCP_CORK 3
#define TCP_KEEPIDLE 4
#define TCP_KEEPINTVL 5
#define TCP_KEEPCNT 6
#define TCP_SYNCNT 7
#define TCP_LINGER2 8
#define TCP_DEFER_ACCEPT 9
#define TCP_WINDOW_CLAMP 10
#define TCP_INFO 11
#define TCP_QUICKACK 12
#define TCP_CONGESTION 13
#define TCP_MD5SIG 14
#define TCP_COOKIE_TRANSACTIONS 15
#define TCP_THIN_LINEAR_TIMEOUTS 16
#define TCP_THIN_DUPACK 17
#define TCP_USER_TIMEOUT 18
#define TCP_REPAIR 19
#define TCP_REPAIR_QUEUE 20
#define TCP_QUEUE_SEQ 21
#define TCP_REPAIR_OPTIONS 22
#define TCP_FASTOPEN 23
#define TCP_TIMESTAMP 24
#define TCP_NOTSENT_LOWAT 25

#define TCP_CC_INFO 26

#define TCP_SAVE_SYN 27

#define TCP_SAVED_SYN 28

#define TCP_REPAIR_WINDOW 29
#define TCP_FASTOPEN_CONNECT 30
#define TCP_ULP 31
#define TCP_MD5SIG_EXT 32
#define TCP_FASTOPEN_KEY 33
#define TCP_FASTOPEN_NO_COOKIE 34
#define TCP_ZEROCOPY_RECEIVE 35
#define TCP_INQ 36

#define TCP_CM_INQ TCP_INQ
#define TCP_TX_DELAY 37

#define TCP_REPAIR_ON 1
#define TCP_REPAIR_OFF 0
#define TCP_REPAIR_OFF_NO_WP -1

#if defined(__BSD_VISIBLE_)
#include <stdint.h>
#include <sys/socket.h>
#include <sys/types.h>

typedef uint32_t tcp_seq;

struct tcphdr {
  __extension__ union {
    struct {
      uint16_t th_sport;
      uint16_t th_dport;
      tcp_seq th_seq;
      tcp_seq th_ack;
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint8_t th_x2 : 4;
      uint8_t th_off : 4;
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint8_t th_off : 4;
      uint8_t th_x2 : 4;
#endif
      uint8_t th_flags;
#define TH_FIN 0x01
#define TH_SYN 0x02
#define TH_RST 0x04
#define TH_PUSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
      uint16_t th_win;
      uint16_t th_sum;
      uint16_t th_urp;
    };
    struct {
      uint16_t source;
      uint16_t dest;
      uint32_t seq;
      uint32_t ack_seq;
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint16_t res1 : 4;
      uint16_t doff : 4;
      uint16_t fin : 1;
      uint16_t syn : 1;
      uint16_t rst : 1;
      uint16_t psh : 1;
      uint16_t ack : 1;
      uint16_t urg : 1;
      uint16_t res2 : 2;
#elif __BYTE_ORDER == __BIG_ENDIAN
      uint16_t doff : 4;
      uint16_t res1 : 4;
      uint16_t res2 : 2;
      uint16_t urg : 1;
      uint16_t ack : 1;
      uint16_t psh : 1;
      uint16_t rst : 1;
      uint16_t syn : 1;
      uint16_t fin : 1;
#else
#error "Adjust your <endian.h> defines"
#endif
      uint16_t window;
      uint16_t check;
      uint16_t urg_ptr;
    };
  };
};

enum {
  TCP_ESTABLISHED = 1,
  TCP_SYN_SENT,
  TCP_SYN_RECV,
  TCP_FIN_WAIT1,
  TCP_FIN_WAIT2,
  TCP_TIME_WAIT,
  TCP_CLOSE,
  TCP_CLOSE_WAIT,
  TCP_LAST_ACK,
  TCP_LISTEN,
  TCP_CLOSING
};

#define TCPOPT_EOL 0
#define TCPOPT_NOP 1
#define TCPOPT_MAXSEG 2
#define TCPOLEN_MAXSEG 4
#define TCPOPT_WINDOW 3
#define TCPOLEN_WINDOW 3
#define TCPOPT_SACK_PERMITTED 4
#define TCPOLEN_SACK_PERMITTED 2
#define TCPOPT_SACK 5
#define TCPOPT_TIMESTAMP 8
#define TCPOLEN_TIMESTAMP 10
#define TCPOLEN_TSTAMP_APPA (TCPOLEN_TIMESTAMP + 2)

#define TCPOPT_TSTAMP_HDR                                        \
  (TCPOPT_NOP << 24 | TCPOPT_NOP << 16 | TCPOPT_TIMESTAMP << 8 | \
   TCPOLEN_TIMESTAMP)

#define TCP_MSS 512

#define TCP_MAXWIN 65535

#define TCP_MAX_WINSHIFT 14

#define SOL_TCP 6

#define TCPI_OPT_TIMESTAMPS 1
#define TCPI_OPT_SACK 2
#define TCPI_OPT_WSCALE 4
#define TCPI_OPT_ECN 8
#define TCPI_OPT_ECN_SEEN 16
#define TCPI_OPT_SYN_DATA 32

enum tcp_ca_state {
  TCP_CA_Open = 0,
  TCP_CA_Disorder = 1,
  TCP_CA_CWR = 2,
  TCP_CA_Recovery = 3,
  TCP_CA_Loss = 4
};

struct tcp_info {
  uint8_t tcpi_state;
  uint8_t tcpi_ca_state;
  uint8_t tcpi_retransmits;
  uint8_t tcpi_probes;
  uint8_t tcpi_backoff;
  uint8_t tcpi_options;
  uint8_t tcpi_snd_wscale : 4, tcpi_rcv_wscale : 4;

  uint32_t tcpi_rto;
  uint32_t tcpi_ato;
  uint32_t tcpi_snd_mss;
  uint32_t tcpi_rcv_mss;

  uint32_t tcpi_unacked;
  uint32_t tcpi_sacked;
  uint32_t tcpi_lost;
  uint32_t tcpi_retrans;
  uint32_t tcpi_fackets;

  uint32_t tcpi_last_data_sent;
  uint32_t tcpi_last_ack_sent;
  uint32_t tcpi_last_data_recv;
  uint32_t tcpi_last_ack_recv;

  uint32_t tcpi_pmtu;
  uint32_t tcpi_rcv_ssthresh;
  uint32_t tcpi_rtt;
  uint32_t tcpi_rttvar;
  uint32_t tcpi_snd_ssthresh;
  uint32_t tcpi_snd_cwnd;
  uint32_t tcpi_advmss;
  uint32_t tcpi_reordering;

  uint32_t tcpi_rcv_rtt;
  uint32_t tcpi_rcv_space;

  uint32_t tcpi_total_retrans;
};

#define TCP_MD5SIG_MAXKEYLEN 80

#define TCP_MD5SIG_FLAG_PREFIX 1

struct tcp_md5sig {
  struct sockaddr_storage tcpm_addr;
  uint8_t tcpm_flags;
  uint8_t tcpm_prefixlen;
  uint16_t tcpm_keylen;
  uint32_t __tcpm_pad;
  uint8_t tcpm_key[TCP_MD5SIG_MAXKEYLEN];
};

struct tcp_repair_opt {
  uint32_t opt_code;
  uint32_t opt_val;
};

enum {
  TCP_NO_QUEUE,
  TCP_RECV_QUEUE,
  TCP_SEND_QUEUE,
  TCP_QUEUES_NR,
};

#define TCP_COOKIE_MIN 8
#define TCP_COOKIE_MAX 16
#define TCP_COOKIE_PAIR_SIZE (2 * TCP_COOKIE_MAX)

#define TCP_COOKIE_IN_ALWAYS (1 << 0)
#define TCP_COOKIE_OUT_NEVER (1 << 1)

#define TCP_S_DATA_IN (1 << 2)
#define TCP_S_DATA_OUT (1 << 3)

#define TCP_MSS_DEFAULT 536U
#define TCP_MSS_DESIRED 1220U

struct tcp_cookie_transactions {
  uint16_t tcpct_flags;
  uint8_t __tcpct_pad1;
  uint8_t tcpct_cookie_desired;
  uint16_t tcpct_s_data_desired;
  uint16_t tcpct_used;
  uint8_t tcpct_value[TCP_MSS_DEFAULT];
};

struct tcp_repair_window {
  uint32_t snd_wl1;
  uint32_t snd_wnd;
  uint32_t max_window;
  uint32_t rcv_wnd;
  uint32_t rcv_wup;
};

struct tcp_zerocopy_receive {
  uint64_t address;
  uint32_t length;
  uint32_t recv_skip_hint;
};
#endif /* __BSD_VISIBLE_ */

#endif /* !_NETINET_TCP_H */
