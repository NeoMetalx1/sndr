#include "config/proto_hdr.h"
#include "setup/rx/socket_setup_rx.h"

#define IP_ADDR_STR_LEN 16

int main () {
    Rx rx;

    const char* rx_ip = "192.168.0.140";
    uint32_t port = DEFAULT_PORT;
    char connected_ip[IP_ADDR_STR_LEN];  // test

    // Init
    if (rx_init(&rx, rx_ip, port) < 0) {
        perror("Failed to init");
        return -1;
    } else {
        printf("[+] Init Rx successful\n");
    }
    
    // Accept
    if (rx_accept(&rx, &rx.tx_addr) < 0) {
        perror("Failed to accept");
        return -1;
    } else {
        printf("[+] Accept connection successful\n");
        if (inet_ntop(AF_INET, &rx.tx_addr.sin_addr, connected_ip, IP_ADDR_STR_LEN) != NULL)
            printf("[+] New connetion: %s\n", connected_ip);
    }

    // Close
    if (rx_close(&rx) < 0) {
        return -1;
    } else {
        printf("[+] Close Rx successful\n");
    }

    return 0;
}
