#include "transmit.h"

int send_file(Tx *tx, const char* file_path, uint32_t file_id, uint64_t chunk_size) {
    FILE *file;
    int file_size;

    file = fopen(file_path, "rb");

    if (file == NULL) {
        perror("Failed to open file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Send start header
    sndr_hdr_t start_header = {
        .type = SNDR_START,
        .id = file_id,
        .file_size = file_size,
        .chunk_size = chunk_size,
        .offset = 0
    };

    tx_send(tx, &start_header, sizeof(sndr_hdr_t));   


    // Send chunk header and data 
    char *chunk = malloc(chunk_size);
    if (!chunk) return -1;

    uint64_t offset = 0;
    size_t bytesRead;
    sndr_hdr_t chunk_header;

    while ((bytesRead = fread(chunk, 1, chunk_size, file)) > 0) {

        chunk_header.type = header_type.SNDR_CHUNK;
        chunk_header.id = file_id;
        chunk_header.file_size = file_size;
        chunk_header.chunk_size = bytesRead;
        chunk_header.offset = offset;

        tx_send(tx, &chunk_header, sizeof(sndr_hdr_t));
        tx_send(tx, chunk, bytesRead);

        offset += bytesRead;
    }

    free(chunk);

    // Send end of file header
    sndr_hdr_t end_header = {
        .type = SNDR_END,
        .id = file_id,
        .file_size = file_size,
        .chunk_size = chunk_size,
        .offset = offset
    };

    tx_send(tx, &end_header, sizeof(sndr_hdr_t));

    fclose(file);
    return 0;
}
