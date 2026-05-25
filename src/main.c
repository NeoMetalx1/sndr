#include "config/proto_hdr.h"
#include "setup/rx/socket_setup_rx.h"
#include "setup/tx/socket_setup_tx.h"

#define IP_ADDR_STR_LEN 16

int rx_run_test(Rx *rx, const char* ip, uint32_t port);
int tx_run_test(Tx *tx, const char* ip, uint32_t port, void *data, size_t size);

int main() {
    //Rx rx;
    Tx tx;
    const char* rx_ip = "127.0.0.1";
  
    //int rx_result = rx_run_test(&rx, rx_ip, DEFAULT_PORT);
    int tx_result = tx_run_test(&tx, rx_ip, DEFAULT_PORT, "hello", sizeof("hello"));

    // printf("Rx result: %d\n", rx_result);
    printf("Tx result: %d\n", tx_result);
}

int rx_run_test (Rx *rx, const char* ip, uint32_t port) {

    char connected_ip[IP_ADDR_STR_LEN];  // test

    // Init
    if (rx_init(rx, ip, port) < 0) {
        perror("Failed to init");
        return -1;
    } else {
        printf("[+] Init Rx successful\n");
    }
    
    // Accept
    if (rx_accept(rx, &rx->tx_addr) < 0) {
        perror("Failed to accept");
        return -1;
    } else {
        printf("[+] Accept connection successful\n");
        if (inet_ntop(AF_INET, &rx->tx_addr.sin_addr, connected_ip, IP_ADDR_STR_LEN) != NULL)
            printf("[+] New connetion: %s\n", connected_ip);
    }

    // Close
    if (rx_close(rx) < 0) {
        return -1;
    } else {
        printf("[+] Close Rx successful\n");
    }

    return 0;
}

int tx_run_test (Tx *tx, const char* ip, uint32_t port, void *data, size_t size) {

    // Init
    if (tx_init(tx, ip, port) < 0) {
        perror("Failed to init");
        return -1;
    } else {
        printf("[+] Init Tx successful\n");
    }

    // Connect
    if (tx_connect(tx) < 0) {
        perror("Failed to connect");
        return -1;
    } else {
        printf("[+] Connect successful\n");
    }
    
    // Send
    int bytes_sent = tx_send(tx, data, size);
    if (bytes_sent < 0) {
        perror("Failed to send");
        return -1;
    } else {
        printf("[+] Sent bytes: %d\n", bytes_sent);
    }

    // Close
    if (tx_close(tx) < 0) {
        return -1;
    } else {
        printf("[+] Close Tx successfuly\n");
    }

    return 0;
}
