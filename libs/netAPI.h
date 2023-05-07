#import <stdio.h>
#import <unistd.h>
#import <iostream>
#import <sys/socket.h>
#import <sys/types.h>
#import <arpa/inet.h>
#import <netinet/in.h>
#import <netdb.h>
#import <string>
#import <thread>
#include <chrono>
#import "SmartPtr.h"
#import "Core.h"

// --- Коды ошибок---
#define GENERAL_ERROR           -1
#define SOCKET_ERROR            -2
#define BINDING_NET_ERROR       -3
#define CONNECTION_REFUSED      -4
#define ACCEPT_LISTENER_ERROR   -5
#define SENDING_ERROR           -6
#define RECV_ERROR              -7
#define INIT_ERROR              -8
#define HTTP_H_ERROR            -9
#define OK                       0

// ---Константы для апи---
#define CLIENT                   1
#define SERVER                   2
#define CIPHER                   3
#define BUFFER                   4

// ---Сетевые константы---
#define NONBLOCK     SOCK_NONBLOCK
#define TCP            SOCK_STREAM
#define UDP             SOCK_DGRAM
#define RAW               SOCK_RAW
#define AF                 AF_INET
#define PF                 PF_INET

// ---Константы сетевых параметров---
#define LISTENER         "0.0.0.0"
#define LOOPBACK       "127.0.0.1"
#define STANDART_PORT         4444

class net {
public:
    int init(core::int32_t, sockaddr_in);
    void init_socket(sockaddr_in *, core::int8_t *, core::int32_t);
    void _recv(sockaddr_in, void *, sockaddr *, socklen_t *);
    void _recv_loop(sockaddr_in, void *, sockaddr *, socklen_t *);
    void _send(sockaddr_in, void *, size_t);
    void shell_client(sockaddr_in, core::int32_t);
    void shell_server(sockaddr_in, core::int32_t);
    void getserviceaddr(int, char **);
};