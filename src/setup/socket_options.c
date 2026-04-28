#include "socket_options.h"

int init_socket(int *fd, sockaddr_in *addr, const char *ip, uint32_t port) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;

    memset(addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    if (ip == NULL) {
        addr.sin_addr.s_addr = INADDR_ANY;
    }
    else {
        if ( inet_pton(AF_INET, ip, addr.sin_addr) <= 0) {
            perror("[ERROR] Failed to convert ip in network byte order: (inet_pton returned value -1)");    
            return -1;
        }
    }
    return 0;
}


int bind_socket(int *fd, sockaddr_in *addr, socklen_t *addrlen) {
    return (bind(fd, (struct sockaddr *)addr, addrlen));
}


int listen_socket(int *fd, int conn_num) {
    return listen(fd, conn_num);
}


int accept_socket(int *fd, sockaddr_in *addr, socklen_t *addrlen) {
    return accept(fd, (struct sockaddr *)addr, addrlen);
}


int send_data(int *fd, void *data, size_t data_size, int flags) {
    const char *ptr = (const char *)data;
    size_t bytes_sended = 0;

    while(bytes_sended < data_size) {
        ssize_t sent = send(fd, ptr + bytes_sended, data_size - bytes_sended, 0);
        if (sent <= 0) return -1;
        bytes_sended += sent;
    }
    return bytes_sended;
}
