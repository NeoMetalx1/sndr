#pragma once

#include "config/proto_hdr.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd>
#include <cstdint>

#define DEFAULT_PORT 8990
#define CHECK(x) if ((x) < 0) return -1;

typedef struct {
    int fd;
    struct sockaddr_in addr;
} Socket;


int init_socket(Socket& socket, const char *ip, uint32_t port);

int bind_socket(Socket *s);

int listen_socket(Socket *s, const uint64_t& conn_num);

int accept_socket(Socket *s, sockaddr *addr, socklen_t *addrlen);

int send_data(Socket *s, const char* data, size_t& data_size, const int& flags = 0);

int recv_data(Socket *s, const char *buffer, size_t& expected_data_size, const int& flags = 0);

int close_socket(Socket *s);
