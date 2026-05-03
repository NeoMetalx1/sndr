#include "config/proto_hdr.h"
#include "setup/socket_options.h"

#define DEFAULT_CHUNK_SIZE 32767

typedef struct {
    Socket sock;
    struct sockaddr_in tx_addr;  // tx sockaddr to store it after accept()
    char buffer[DEFAULT_CHUNK_SIZE];
} Rx;


int rx_init(Rx *rx, const char *ip, uint32_t port);

int rx_accept(Rx *rx, struct sockaddr_in *addr);

int rx_recv(Rx *rx);

int rx_close(Rx *rx);
