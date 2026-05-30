#include "transmit.h"

int tx_send_file(Socket *s, const char *filepath, uint32_t file_id, uint64_t chunk_size) {
    size_t file_size = get_file_size(filepath);

    sndr_hdr_t start_header = {
        .type = SNDR_START,
        .id = file_id,
        .file_size = file_size,
        .chunk_size = chunk_size,
        .offset = 0
    };
    
    // Send start header
    send_data(s, &start_header, sizeof(start_header), 0);

    
}
