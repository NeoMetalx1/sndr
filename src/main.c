#include "config/proto_hdr.h"
#include "setup/socket_setup_rx.h"

int main () {
    Rx rx;

    const char* rx_ip = "127.0.0.1";
    uint32_t port = DEFAULT_PORT;
    struct sockaddr_in txAddr;

    // Init
    if (rx_init(&rx, rx_ip, port) < 0) {
        perror("Failed to init");
        return -1;
    } else {
        printf("[+] Init Rx successful\n");
    }
    
    // Accept
    if (rx_accept(&rx, &txAddr, sizeof(txAddr)) < 0) {
        perror("Failed to accept");
        return -1;
    } else {
        printf("[+] Accept connection successful\n");
    }

    // Close
    if (rx_close(&rx) < 0) {
        return -1;
    } else {
        printf("[+] Close Rx successful\n");
    }

    return 0;
}
