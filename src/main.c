#include "config/proto_hdr.h"
#include "setup/socket_setup_rx.h"

int main () {
    Rx *rx;
    const char *rx_ip = "127.0.0.1";
    uint32_t port = DEFAULT_PORT;

    int init_stat = rx_init(rx, rx_ip, port);

    if (init_stat == 0) {
        printf("[+] Init Rx succesfull");
    }

    return 0;
}
