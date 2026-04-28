#include "socket_options.h"

#define DEFAULT_CHUNK_SIZE 32767

typedef struct {
    Socket sock;
    const char* buffer[DEFAULT_CHUNK_SIZE];
} Rx
