
 /*-O//\           __     __
   |-gfo\         |__| | |  | |\ | ™
   |!y°o:\        |  __| |__| | \| v8.0
   |y"s§+`\       multi-master, multi-media communications bus system framework
  /so+:-..`\      Copyright 2010-2017 by Giovanni Blu Mitolo gioscarab@gmail.com
  |+/:ngr-*.`\
  |5/:%&-a3f.:;\
  \+//u/+g%{osv,,\
    \=+&/osw+olds.\\
       \:/+-.-°-:+oss\
        | |       \oy\\
        > <
 ______-| |-___________________________________________________________________

PJON™ is a self-funded, no-profit open-source project created and mantained by
Giovanni Blu Mitolo with the support ot the internet community if you want
to see the PJON project growing with a faster pace, consider a donation
at the following link: https://www.paypal.me/PJON

For the PJON™ Protocol specification see the specification directory.

PJON™ Standard compliant tools:
- ModuleInterface - Easy config and value sync between IOT modules
 https://github.com/fredilarsen/ModuleInterface
- PJON-python - PJON running on Python by Zbigniew Zasieczny (obsolete)
 https://github.com/Girgitt/PJON-python
- Logic analyzer by Andrew Grande (obsolete)
 https://github.com/aperepel/saleae-pjon-protocol-analyzer
 ______________________________________________________________________________

Copyright 2010-2017 by Giovanni Blu Mitolo gioscarab@gmail.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once
#include "utils/PJON_CRC8.h"
#include "utils/PJON_CRC32.h"

/* Id used for broadcasting to all devices */
#define PJON_BROADCAST        0

/* Master device id */
#define PJON_MASTER_ID      254

/* Device id of still unindexed devices */
#define PJON_NOT_ASSIGNED   255

/* Maximum devices handled by master */
#ifndef PJON_MAX_DEVICES
  #define PJON_MAX_DEVICES   25
#endif

/* Communication modes */
#define PJON_SIMPLEX        150
#define PJON_HALF_DUPLEX    151

/* Protocol symbols */
#define PJON_ACK              6
#define PJON_BUSY           666
#define PJON_NAK             21

/* Dynamic addressing */
#define PJON_ID_ACQUIRE     199
#define PJON_ID_REQUEST     200
#define PJON_ID_CONFIRM     201
#define PJON_ID_NEGATE      203
#define PJON_ID_LIST        204
#define PJON_ID_REFRESH     205

/* INTERNAL CONSTANTS */
#define PJON_FAIL         65535
#define PJON_TO_BE_SENT      74

/* HEADER BITS DEFINITION: */

/* 0 - Local network
   1 - Shared  network */
#define PJON_MODE_BIT       0B00000001
/* 0 - No info inclusion
   1 - Local:  Sender device id included
       Shared: Sender device id + Sender bus id */
#define PJON_TX_INFO_BIT    0B00000010
/* 0 - Acknowledgement disabled
   1 - Acknowledgement enabled */
#define PJON_ACK_REQ_BIT    0B00000100
/* 0 - Synchronous acknowledgement requested
   1 - Asynchronous acknowledgement requested */
#define PJON_ACK_MODE_BIT   0B00001000
/* 0 - Not addressing related
   1 - Addressing related */
#define PJON_ADDRESS_BIT    0B00010000
/* 0 - CRC8 (1 byte) included at the end of the packet
   1 - CRC32 (4 bytes) included at the end of the packet */
#define PJON_CRC_BIT        0B00100000
/* 0 - 1 byte length (max 255 characters)
   1 - 2 bytes length (max 65535 characters) */
#define PJON_EXT_LEN_BIT    0B01000000
/* 0 - 1 byte header
   1 - 2 bytes header */
#define PJON_EXT_HEAD_BIT   0B10000000

/* EXTENDED HEADER BITS DEFINITION: */

/* 0 - No routing
   1 - Routing */
#define PJON_ROUTING_BIT    0B0100000000000000
/* 0 - No segmentation
   1 - Segmentation */
#define PJON_SEGM_BIT       0B0010000000000000
/* 0 - Not including session
   1 - Including session */
#define PJON_SESSION_BIT    0B0001000000000000
/* 0 - No parity included
   1 - Parity included */
#define PJON_PARITY_BIT     0B0000100000000000
/* 0 - Not encoded
   1 - Encoded */
#define PJON_ENCODING_BIT   0B0000010000000000
/* 0 - No data compression
   1 - Data compression */
#define PJON_DATA_COMP_BIT  0B0000001000000000
/* 0 - Not encrypted
   1 - Encrypted */
#define PJON_ENCRYPTION_BIT 0B0000000100000000

/* ERRORS: */
#define PJON_CONNECTION_LOST     101
#define PJON_PACKETS_BUFFER_FULL 102
#define PJON_CONTENT_TOO_LONG    104
#define PJON_ID_ACQUISITION_FAIL 105
#define PJON_DEVICES_BUFFER_FULL 254

/* CONSTRAINTS: */

/* Packet buffer length, if full PJON_PACKETS_BUFFER_FULL error is thrown.
   The packet buffer is preallocated, so its length strongly affects
   memory consumption */
#ifndef PJON_MAX_PACKETS
  #define PJON_MAX_PACKETS 5
#endif

/* Max packet length, higher if necessary.
   The max packet length defines the length of packets pre-allocated buffers
   so it strongly affects memory consumption */
#ifndef PJON_PACKET_MAX_LENGTH
  #define PJON_PACKET_MAX_LENGTH 50
#endif

/* If set to true avoids async ack code memory allocation if not used
   (it saves around 1kB of memory) */
#ifndef PJON_INCLUDE_ASYNC_ACK
  #define PJON_INCLUDE_ASYNC_ACK false
#endif

/* Maximum packet ids record kept in memory (to avoid duplicated exchanges) */
#ifndef PJON_MAX_RECENT_PACKET_IDS
  #define PJON_MAX_RECENT_PACKET_IDS 10
#endif

/* If set to true ensures packet ordered sending */
#ifndef PJON_ORDERED_SENDING
  #define PJON_ORDERED_SENDING false
#endif

/* Dynamic addressing timing constants:
   Maximum number of device id collisions during auto-addressing */
#define PJON_MAX_ACQUIRE_ID_COLLISIONS 10
/* Delay between device id acquisition and self request */
#define PJON_ACQUIRE_ID_DELAY        1000
/* Maximum id scan time (6 seconds) */
#define PJON_ID_SCAN_TIME         6000000
/* Master free id broadcast response interval (0.1 seconds) */
#define PJON_ID_REQUEST_INTERVAL   100000
/* Master ID_REQUEST and ID_NEGATE timeout */
#define PJON_ADDRESSING_TIMEOUT   2900000
/* Master reception time during LIST_ID broadcast (75 milliseconds) */
#define PJON_LIST_IDS_TIME          75000

struct PJON_Packet {
  uint8_t  attempts;
  char     content[PJON_PACKET_MAX_LENGTH];
  uint16_t length;
  uint32_t registration;
  uint16_t state;
  uint32_t timing;
};

struct PJON_Packet_Record {
  uint16_t id;
  uint8_t  header;
  uint8_t  sender_id;
  uint8_t  sender_bus_id[4];
};

/* Last received packet Metainfo */
struct PJON_Packet_Info {
  uint16_t header = 0;
  uint16_t id = 0;
  uint8_t receiver_id = 0;
  uint8_t receiver_bus_id[4];
  uint8_t sender_id = 0;
  uint8_t sender_bus_id[4];
};

typedef void (* PJON_Receiver)(
  uint8_t *payload,
  uint16_t length,
  const PJON_Packet_Info &packet_info
);

static void PJON_dummy_receiver_handler(
  uint8_t *payload,
  uint16_t length,
  const PJON_Packet_Info &packet_info
) {};

typedef void (* PJON_Error)(uint8_t code, uint8_t data);

static void PJON_dummy_error_handler(uint8_t code, uint8_t data) {};
