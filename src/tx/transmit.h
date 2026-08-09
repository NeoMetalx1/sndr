#pragma once

#include "config/proto_hdr.h"
#include "setup/socket_options.h"
#include "file/file_options.h"

int tx_send_start_header(Socket *s, uint32_t file_id, uint64_t file_size, uint64_t chunk_size);

int tx_send_end_header(Socket *s, uint32_t file_id, uint64_t file_size, uint64_t chunk_size);

int tx_send_chunk(Socket *s, FILE *file, uint32_t file_id, uint64_t file_size, uint64_t chunk_size);

int tx_send_file(Socket *s, const char *filepath, uint32_t file_id, uint64_t chunk_size);
