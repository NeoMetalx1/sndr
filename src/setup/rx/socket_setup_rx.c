#include "socket_setup_rx.h"


int rx_init(Rx *rx, const char *ip, uint32_t port) {
    if (!rx) return -1;

    if (init_socket(&rx->sock, ip, port) < 0) {
        perror("[ERROR] Failed to initialize Rx socket");
        return -1;
    }

    if (bind_socket(&rx->sock) < 0) {
        perror("[ERROR] Failed to bind Rx socket");
        return -1;
    }

    if (listen_socket(&rx->sock, 2) < 0) {
        perror("[ERROR] Failed to listen");
        return -1;
    }

    return 0;
}


int rx_accept(Rx *rx, struct sockaddr_in *addr) {
    socklen_t tx_addrlen = sizeof(*addr);

    if (accept_socket(&rx->sock, addr, &tx_addrlen) < 0) {
        perror("[ERROR] Failed to accept connection in Rx socket");
        return -1;
    }
    return 0;
}


int rx_recv(Rx *rx) {
    int recv_bytes = recv_data(&rx->sock, rx->buffer, DEFAULT_CHUNK_SIZE, 0);
    if (recv_bytes < 0) {
        perror("[ERROR] Failed to receive data in Rx socket");
        return -1;
    }
    return recv_bytes;
}


int rx_close(Rx *rx) {
    if (!rx) return -1;

    if (close_socket(&rx->sock) < 0) {
        perror("[ERROR] Failed to close Rx socket");
        return -1;
    }

    return 0;
}
