#pragma once

#include <stdint.h>
#include <string.h>
#include <stdio.h>

/*  [sndr_type_e] field of protocol header
 *
 *  Defines type that will be send
 *
 *      [+] SNDR_TEST - send test data to receiver
 *      [+] SNDR_FILE - send chunk of file to receiver
*/
typedef enum {
   SNDR_TEST,
   SNDR_FILE 
} sndr_type_e;


/*  [sndr_hdr_t] header of sndr protocol
 *
 *  0                 bits                    32
 *  v                                         v
 *  |                                         |
 *  +------+                                  +
 *  | type |                                  |
 *  +-----------------------------------------+
 *  |                data_len                 |
 *  +-----------------------------------------+
 *
*/
typedef struct {
  sndr_type_e type;
  uint32_t    data_len;  
} sndr_hdr_t;
