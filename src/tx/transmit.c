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
    send_data(s, &start_header, sizeof(sndr_hdr_t), 0);

    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }
    
    // Send chunk header and chunk
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

        send_data(s, &chunk_header, sizeof(sndr_hdr_t), 0);
        send_data(s, chunk, bytesRead, 0);

        offset += bytesRead;
    }
    free(chunk);   

    // Send end header
    sndr_hdr_t end_header = {
        .type = SNDR_END,
        .id = file_id,
        .file_size = file_size,
        .chunk_size = 0,
        .offset = offset
    };
    send_data(s, &end_header, sizeof(sndr_hdr_t), 0);

    fclose(file);
    return 0;
}
