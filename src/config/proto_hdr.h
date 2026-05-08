#pragma once

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*  [sndr_type_e] field of protocol header
 *
 *  Defines type that will be send
 *
 *      [+] SNDR_TEST - send test data to receiver
 *      [+] SNDR_FILE - send chunk of file to receiver
*/
typedef enum {
   SNDR_TEST,
   SNDR_START,
   SNDR_FILE, 
   SNDR_END
} sndr_type_e;


/*  [sndr_hdr_t] header of sndr protocol
 *
 *  0                 bits                    32
 *  v                                         v
 *  |                                         |
 *  +------+------+------+------+------+------+                                  +
 *  |    type     |                           |
 *  +-----------------------------------------+
 *  |                data_len                 |
 *  +-----------------------------------------+
 *
*/
typedef struct {
  uint8_t  type;
  uint64_t file_len;
  uint32_t data_len;  
  uint64_t offset;
} sndr_hdr_t;
