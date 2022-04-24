#include "Server.hpp"

Server::Server() {

}

Server::Server(Server const & src) {


}

Server & Server::operator=(Server const & src) {
	return *this;
}

Server::~Server() {

}


void	Server::createSocket() {

	sock_fd = socket(AF_INET, SOCK_STREAM, 0); 
}

void	Server::bindSocket() {

}

void	Server::deleteSocket() {

}
