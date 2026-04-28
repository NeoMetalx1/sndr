#pragma once

#include "config/proto_hdr.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd>
#include <cstdint>


int init_socket(int *fd, sockaddr_in *addr, const char *ip, uint32_t port);

int bind_socket(int *fd, sockaddr_in *addr, socklen_t *addrlen);

int listen_socket(int *fd, int conn_num);

int accept_socket(int *fd, sockaddr_in *addr, socklen_t *addrlen);

int send_data(int *fd, void *data, size_t data_size, int flags);

int recv_data(int *fd, const char *buffer, size_t expected_data_size, int flags);

int close_socket(int *fd);

