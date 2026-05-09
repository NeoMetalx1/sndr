#include "socket_setup_tx.h"

int tx_init(Tx *tx, const char *ip, uint32_t port) {
    if (!tx) return -1;

    if (init_socket(&tx->sock, ip, port) < 0) {
        perror("[ERROR] Failed to init Tx socket");
        return -1;
    }
    return 0;
}


int tx_connect(Tx *tx) {
    socklen_t addrlen = sizeof(tx->sock.addr);
    if (connect_socket(&tx->sock, &tx->sock.addr, addrlen) < 0) {
        perror("[ERROR] Failed to connect Tx socket");
        return -1;
    }
    return 0;
}


int tx_send(Tx *tx, void *data) {
    int sent_bytes = send_data(&tx->sock, data, sizeof(*data), 0);
    if (sent_bytes < 0) {
        perror("[ERROR] Failed to send data from Tx socket");
        return -1;
    }
    return sent_bytes;
}


int tx_close(Tx *tx) {
    if (!tx) return -1;
    
    if (close_socket(&tx->sock) < 0) {
        perror("[ERROR] Failed to close Tx socket");
        return -1;
    }
    return 0;
}
