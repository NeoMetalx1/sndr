#pragma once

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_CHUNK_SIZE 16000
#define DEFAULT_PORT 8990

/*  [sndr_type_e] field of protocol header
 *
 *  Defines type that will be send
 *
 *      [+] SNDR_TEST - send test data to receiver
 *      [+] SNDR_START - send data to identify start of file
 *      [+] SNDR_CHUNK - send chunk of file to receiver
 *      [+] SNDR_END - send data to identify end of file
*/
typedef enum {
   SNDR_TEST,
   SNDR_START,
   SNDR_CHUNK, 
   SNDR_END
} sndr_type_e;


/*  [sndr_hdr_t] header of sndr protocol
 *
 *
*/
typedef struct {
  uint8_t  type;
  uint32_t id;
  uint64_t file_size;
  uint32_t chunk_size;  
  uint64_t offset;
} sndr_hdr_t;
