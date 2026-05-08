#include "setup_socket_tx.h"

int tx_init(Tx *tx, const char *ip, uint32_t port) {
    if (!tx) return -1;

    if (init_socket(&tx->sock, ip, port) < 0) {
        perror("[ERROR] Failed to init Tx socket");
        return -1;
    }
    return 0;
}


int tx_connect(Tx *tx) {
    socklen_t addrlen = sizeof(&tx->rx_addr);
    if (connect_socket(&tx->sock, &tx->rx_addr, addrlen) < 0) {
        perror("[ERROR] Failed to connect Tx socket");
        return -1;
    }
    return 0;
}


int tx_send(Tx *tx) // Stop here
