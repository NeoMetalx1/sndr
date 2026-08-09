#include "receive.h"

int rx_receive_file(Socket *s, const char *filepath) {
    FILE *file = fopen(filepath, "wb");
    if(!file) {
        perror("Failed to open file");
        return -1;
    }
    sndr_hdr_t header;

    char buffer[DEFAULT_CHUNK_SIZE];

    while (1) {
        if (recv_data(s, &header, sizeof(header), 0) <= 0) {
            perror("Failed to receive data");
            return -1;
        }

        switch (header.type) {
            case SNDR_START: {
                printf("--- RECV HEADER ---\n");
                printf("TYPE: SNDR_START\n");
                printf("FILE_ID: %d\n", header.id);
                printf("FILE_SIZE: %lu\n", header.file_size);
                printf("CHUNK_SIZE: %d\n", header.chunk_size);
                printf("OFFSET: %lu\n", header.offset);
                printf("[Opening file]\n");
                break;
            }
            case SNDR_CHUNK: {
                printf("---RECV HEADER ---\n");
                printf("TYPE: SNDR_CHUNK\n");
                printf("FILE_ID: %d\n", header.id);
                printf("FILE_SIZE: %lu\n", header.file_size);
                printf("CHUNK_SIZE: %d\n", header.chunk_size);
                printf("OFFSET: %lu\n", header.offset);

                if (!file) {
                    perror("File for write is closed");
                    return -1;
                }

                if (header.chunk_size > DEFAULT_CHUNK_SIZE) {
                    perror("Chunk size too big");
                    return -1;
                }

                if (recv_data(s, buffer, header.chunk_size, 0) <= 0) {
                    perror("Failed to recv chunk");
                    return -1;
                }

                int writeBytes = fwrite(buffer, 1, header.chunk_size, file);

                printf("Write to file: %d bytes\n", writeBytes);

                break;
            } 

            case SNDR_END: {
                printf("---RECV HEADER ---\n");   
                printf("TYPE: SNDR_END\n"); 

                printf("END OF TRANSMIT\n");

                if (file) fclose(file);
                return 0;
            }

            default:
                printf("Unknown header\n");
                return -1;
       }

    }
    return 0;
}
