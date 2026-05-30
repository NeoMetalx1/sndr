#include "receive.h"

int rx_receive_file(Socket *s, const char *filepath) {
    FILE *file = NULL;
    sndr_hdr_t header;

    while (1) {
        if (recv_data(s, &header, sizeof(sndr_hdr_t), 0) <= 0) {
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

                file = fopen(filepath, "wb");
                if(!file) {
                    perror("Failed to open file");
                    return -1;
                }
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

                char *buffer = malloc(header.chunk_size);
                if (!buffer) {
                    perror("Failed to create buffer to write recv data");
                    return -1;
                }

                if (recv_data(s, buffer, header.chunk_size, 0) <= 0) {
                    perror("Failed to recv chunk");
                    free(buffer);
                    return -1;
                }

                fseek(file, header.offset, SEEK_SET);
                int writeBytes = fwrite(buffer, 1, header.chunk_size, file);

                printf("Write to file: %d bytes\n", writeBytes);

                free(buffer);
                break;
            } 

            case SNDR_END: {
                printf("---RECV HEADER ---\n");   
                printf("TYPE: SNDR_END\n"); 

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
