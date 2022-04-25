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

void	Server::handleError(mErrors Error) {
	switch (Error) {
		case createSocketError:
			std::cerr << "Can't create a socket." << std::endl;
			break;
		case bindError:
			std::cerr << "Can't connect to port " << mPort << ". Errno: " << errno << std::endl;
			break;
		case listenSocketError:
			std::cerr << "Failed to listen to socket. Errno: " << errno << std::endl;
			break; 
	}
	exit(-1);
}

void	Server::createSocket() {
	mSockFd = socket(AF_INET, SOCK_STREAM, 0); 
	if (mSockFd < 0)
		handleError(createSocketError);
}

void	Server::bindSocket() {

	//maybe setsockopt later???
	mSockAddr.sin_family = AF_INET;
	mSockAddr.sin_addr.s_addr = mIP;
	mSockAddr.sin_port = htons(mPort);
	if (bind(mSockFd, (struct sockaddr*)&mSockAddr, sizeof(sockaddr)) < 0) {
		handleError(bindError);
	}
}

void	Server::listenSocket() {
	if (listen(mSockFd, 128) < 0)
		handleError(listenSocketError);
}

void Server::acceptConnection() {
	size_t addrlen = sizeof(mSockAddr);
	int clientSocket = accept(mSockFd, (struct sockaddr*)&mSockAddr, (socklen_t*)&addrlen);
}

void	Server::deleteSocket() {

}
