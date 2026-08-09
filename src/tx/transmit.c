#include "transmit.h"

int tx_send_start_header(Socket *s, uint32_t file_id, uint64_t file_size, uint64_t chunk_size) {
    sndr_hdr_t start_header = {
        .type = SNDR_START,
        .id = file_id,
        .file_size = file_size,
        .chunk_size = chunk_size,
        .offset = 0
    };
    
    if (send_data(s, &start_header, sizeof(start_header), 0) <= 0) 
        return -1;
    return 0;
}

int tx_send_end_header(Socket *s, uint32_t file_id, uint64_t file_size, uint64_t chunk_size) {
    sndr_hdr_t end_header = {
        .type = SNDR_END,
        .id = file_id,
        .file_size = file_size,
        .chunk_size = chunk_size,
        .offset = 0
    };

    if (send_data(s, &end_header, sizeof(end_header), 0) <= 0) {
        return -1;
    }
}

int tx_send_chunk(Socket *s, FILE *file, uint32_t file_id, uint64_t file_size, uint64_t chunk_size) {
    sndr_hdr_t chunk_header;
    uint64_t offset = 0;

    char *chunk = malloc(chunk_size);
    if (!chunk) return -1;

    int bytesRead;
    while ((bytesRead = fread(chunk, 1, chunk_size, file)) > 0) {
        
        chunk_header.type = SNDR_CHUNK;
        chunk_header.id = file_id;
        chunk_header.file_size = file_size;
        chunk_header.chunk_size = bytesRead;
        chunk_header.offset = offset;

        if (send_data(s, &chunk_header, sizeof(sndr_hdr_t), 0) <= 0)
            return -1;
        if (send_data(s, chunk, bytesRead, 0) <= 0)
            return -1;

        offset += bytesRead;
    }
    free(chunk);  
    return 0;
}

int tx_send_file(Socket *s, const char *filepath, uint32_t file_id, uint64_t chunk_size) {
    size_t file_size = get_file_size(filepath);

    if (tx_send_start_header(s, file_id, file_size, chunk_size) < 0) {
        perror("Failed to send start header");
        return -1;
    }

    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }
    
    if (tx_send_chunk(s, file, file_id, file_size, chunk_size) < 0) {
        perror("Failed to send chunk");
        return -1;
    }

    if (tx_send_end_header(s, file_id, file_size, chunk_size) < 0) {
        perror("Failed to send end header");
        return -1;
    }

    return 0;
}
