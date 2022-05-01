#include "Server.hpp"

Server::Server(int port, std::string password) : mPort(port), mPassword(password) {

	createSocket();
	bindSocket();
	listenSocket();
}

void Server::operator()() {
	acceptConnection();
	processMessage();
	checkConnection();
	deleteBrokenConnection();
	deleteEmpyChannel();
}

Server::~Server() {

}

<<<<<<< HEAD
void	Server::fatalError(mErrors Error) {
	switch (Error) {
		case bindError:
			std::cerr << "Failed to bind to port " << mPort << std::endl;
			exit(EXIT_FAILURE);
		case createSocketError:
			std::cerr << "Failed to create socket" << std::endl;
			exit(EXIT_FAILURE);
		default:
			exit(EXIT_FAILURE);
	}	
=======
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
>>>>>>> 22f2647277a9c07bfa713cc6c298925d50a60ba6
}

void	Server::createSocket() {
	mSockFd = socket(AF_INET, SOCK_STREAM, 0); 
	if (mSockFd < 0)
<<<<<<< HEAD
		fatalError(createSocketError);
=======
		handleError(createSocketError);
>>>>>>> 22f2647277a9c07bfa713cc6c298925d50a60ba6
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


void 	Server::acceptConnection() {
	size_t addrlen = sizeof(mSockAddr);
	int connection = accept(mSockFd, (struct sockaddr*)&mSockAddr, (socklen_t*)&addrlen);
	
	if (connection < 1)
		return;
	char	host[INET_ADDRSTRLEN];
	//maybe one call in constructor is enough
	inet_ntop(AF_INET, &(mSockAddr.sin_addr), host, INET_ADDRSTRLEN);
	struct pollfd	pfd;
	pfd.fd = connection;
	pfd.events = POLLIN;
	pfd.revents = 0;
	// mUsers.push_back(new User(connection, pfd, host, mServerName));
	mUserDB.addUser(pfd, new User(host, mServerName));
}

void 	Server::processMessage() {
	auto	FDs = mUserDB.getFDs();
	int		pollfd_num = poll(FDs.data(), FDs.size(), 1);

	if (pollfd_num > 0) {
		for (int i=0; mUserDB.size(); i++) {
			if (getFD(i).revents & POLLIN) {
				sendMessage
			}
		}
	}
}

void 	Server::checkConnection() {

}

void 	Server::deleteBrokenConnection() {

}

void 	Server::deleteEmpyChannel() {

}
