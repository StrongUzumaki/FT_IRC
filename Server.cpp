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

void	Server::fatalError(std::string const & errorMessage) {
	switch{
		case bindError
		std::cerr << errorMessage << std::endl;
	
	bindError << "Failed to bind to port " << mPort << ". Errno: " << errno).str()
	exit(-1);
}

void	Server::createSocket() {
	mSockFd = socket(AF_INET, SOCK_STREAM, 0); 
	if (mSockFd < 0)
		fatalError("Can't create a socket.");
}

void	Server::bindSocket() {

	//maybe setsockopt later???
	mSockAddr.sin_family = AF_INET;
	mSockAddr.sin_addr.s_addr = mIP;
	mSockAddr.sin_port = htons(mPort);
	if (bind(mSockFd, (struct sockaddr*)&mSockAddr, sizeof(sockaddr)) < 0) {
		fatalError(bindError);
	}
}

void	Server::deleteSocket() {

}
