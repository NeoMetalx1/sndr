#include "config/proto_hdr.h"
#include "setup/socket_options.h"

typedef struct {
    Socket sock;
    struct sockaddr_in tx_addr;  // tx sockaddr to store it after accept()
} Rx;


int rx_init(Rx *rx, const char *ip, uint32_t port);

int rx_accept(Rx *rx, struct sockaddr_in *addr);

int rx_recv(Rx *rx, char* buffer, size_t expected_size);

int rx_close(Rx *rx);
