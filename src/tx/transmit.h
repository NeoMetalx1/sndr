#pragma once

#include "config/proto_hdr.h"
#include "setup/socket_options.h"
#include "file/file_options.h"

int tx_send_file(const char *filepath);
