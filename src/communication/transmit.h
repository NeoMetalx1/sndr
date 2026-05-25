#pragma once

#include "setup/tx/socket_setup_tx.h"

int send_file(Tx *tx, const char* file_path, uint32_t file_id, uint64_t chunk_size);
