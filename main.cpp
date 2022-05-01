#include "IRC.hpp"
#include "MainErrorHandler.hpp"
#include "Server.hpp"

int main(int ac, char **av) {
	//pohui
	Server server(atoi(av[1]), av[2]);
	server();
	return (0);
}
