#include "file_options.h"

size_t get_file_size(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("[!] Failed to open file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fclose(file);
    return file_size;
}
