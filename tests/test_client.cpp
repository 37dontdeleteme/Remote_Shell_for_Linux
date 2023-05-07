#import "../libs/netAPI.h"

int main() {
	sockaddr_in addr;
	SPtr<net> api;

	api.memory() -> init_socket(&addr, "127.0.0.1", STANDART_PORT);
	api.memory() -> shell_client(addr, BUFFER);
}
