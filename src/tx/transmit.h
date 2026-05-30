#pragma once

#include "config/proto_hdr.h"
#include "setup/socket_options.h"
#include "file/file_options.h"

int tx_send_file(Socket *s, const char *filepath, uint32_t file_id, uint64_t chunk_size);
