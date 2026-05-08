#pragma once

#include "config/proto_hdr.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DEFAULT_PORT 8990

typedef struct {
    int fd;
    struct sockaddr_in addr;
} Socket;

int init_socket(Socket *s, const char *ip, uint32_t port);

int bind_socket(Socket *s);

int listen_socket(Socket *s, int conn_num);

int accept_socket(Socket *s, struct sockaddr_in *addr, socklen_t *addrlen);

int connect_socket(Socket *s, struct sockaddr_in *addr, socklen_t *addrlen);

int send_data(Socket *s, void *data, size_t data_size, int flags);

int recv_data(Socket *s, void *buffer, size_t expected_data_size, int flags);

int close_socket(Socket *s);

