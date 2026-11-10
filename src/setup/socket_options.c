#include "socket_options.h"

int init_socket(Socket *s, const char *ip, uint32_t port) {
    s->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (s->fd < 0) return -1;

    memset(&s->addr, 0, sizeof(s->addr));
    s->addr.sin_family = AF_INET;
    s->addr.sin_port = htons(port);
    
    if (ip == NULL) {
        s->addr.sin_addr.s_addr = INADDR_ANY;
    }
    else {
        if ( inet_pton(AF_INET, ip, &s->addr.sin_addr) <= 0) {
            perror("[ERROR] Failed to convert ip in network byte order: (inet_pton returned value -1)");    
            return -1;
        }
    }
    return 0;
}


int bind_socket(Socket *s) {
    return (bind(s->fd, (struct sockaddr *)&s->addr, sizeof(s->addr)));
}


int listen_socket(Socket *s, int conn_num) {
    return listen(s->fd, conn_num);
}


int accept_socket(Socket *s, struct sockaddr_in *addr, socklen_t *addrlen) {
    return accept(s->fd, (struct sockaddr *)addr, addrlen);
}


int connect_socket(Socket *s, struct sockaddr_in *addr, socklen_t addrlen) {
    return connect(s->fd, (struct sockaddr *)addr, addrlen);
}


int send_data(Socket *s, void *data, size_t data_size, int flags) {
    char *ptr = (char *)data;
    size_t bytes_sended = 0;

    while(bytes_sended < data_size) {
        ssize_t sent = send(s->fd, ptr + bytes_sended, data_size - bytes_sended, flags);
        if (sent <= 0) return -1;
        bytes_sended += sent;
    }
    return bytes_sended;
}


int recv_data(Socket *s, void *buffer, size_t size, int flags) {
    char *ptr = (char *)buffer;
    size_t bytes_received = 0;

    while (bytes_received < size) {
        ssize_t received = recv(s->fd, ptr + bytes_received, size - bytes_received, flags);
        if (received <= 0) return -1;
        bytes_received += received;
    }
    return bytes_received;
}


int close_socket(Socket *s) {
    if (s && s->fd >= 0) {
        close(s->fd);
        s->fd = -1;
        return 0;
    }
    return -1;
}
