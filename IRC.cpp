#include "IRC.hpp"

IRC::IRC(int ac, char **av): mServer(atoi(av[1]), av[2]) {
	//if (ac < 3)
	//	ErrorHandler(wrongNumberofArgs);
// 	int port = atoi(av[1]);
// 	if (port < 1024 || port > 49151)
// 		ErrorHandler(wrongPort);
	// Server(port, av[2]);
}
