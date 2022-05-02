#include "Connector.hpp"

int main(int ac, char **av) {
	//pohui
	//Server server(atoi(av[1]), av[2]);
	//server();
	Connector(6067, "pass", 100)();
	return (0);
}
