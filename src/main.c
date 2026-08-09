#include "tx/transmit.h"
#include "rx/receive.h"


int main(int argc, char** argv) {

    Socket s_tx;
    Socket s_rx;
    
    struct sockaddr_in tx_addr;


    if (strcmp(argv[1], "-t") == 0) {
        init_socket(&s_tx, "192.168.88.248", 8990);
        connect_socket(&s_tx, &s_tx.addr, sizeof(s_tx.addr));
        if(tx_send_file(&s_tx, argv[2], 1, 16000) < 0) {
            perror("Failed to transmit file");
            return -1;
        }
    }

    if (strcmp(argv[1], "-r") == 0) {
        init_socket(&s_rx, "192.168.88.248", 8990);
        bind_socket(&s_rx);
        if (listen_socket(&s_rx, 2) < 0) perror("Failed to listen");
        socklen_t tx_addr_size = sizeof(tx_addr);
        s_tx.fd = accept_socket(&s_rx, &tx_addr, &tx_addr_size);
        if(rx_receive_file(&s_tx, argv[2]) < 0) {
            perror("Failed to recv file");
            return -1;
        }
    }
}
