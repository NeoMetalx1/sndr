#pragma once

#include "config/proto_hdr.h"
#include "setup/socket_options.h"

int rx_receive_file(Socket *s, const char *filepath);
