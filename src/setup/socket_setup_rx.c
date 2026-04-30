#include "socket_setup_rx.h"


int rx_init(Rx *rx, const char *ip, uint32_t port) {
    rx = malloc(sizeof(Rx));

    if (init_socket(&rx->sock, ip, port) < 0) {
        perror("[ERROR] Failed to initialize Rx socket");
        return -1;
    }

    if (bind_socket(&rx->sock) < 0) {
        perror("[ERROR] Failed to bind Rx socket");
        return -1;
    }
                             // todo:fix
    if (listen_socket(&rx->sock, 2) < 0) {
        perror("[ERROR] Failed to listen for connection in Rx socket");
        return -1;
    }
    return 0;
}


int rx_accept(Rx *rx) {
    socklen_t tx_addrlen = sizeof(rx->tx_addr);

    if (accept_socket(&rx->sock, &rx->tx_addr, &tx_addrlen) < 0) {
        perror("[ERROR] Failed to accept connection in Rx socket");
        return -1;
    }
    return 0;
}


int rx_recv(Rx *rx) {
    if (recv_data(&rx->sock, rx->buffer, DEFAULT_CHUNK_SIZE, 0) < 0) {
        perror("[ERROR] Failed to receive data in Rx socket");
        return -1;
    }
    return 0;
}
