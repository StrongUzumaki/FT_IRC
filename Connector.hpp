#pragma once

// socket system
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h> 

#include <stdexcept>

// FIXME
#include <iostream>

#include "User.hpp"
#include "Database.hpp"

// IDEA!
// if the OS fails to give us a socket, we should try again for some time
// we should predefine the timeout

class Connector {
private: // fields
	sockaddr_in mAddr;
	in_addr_t	mIP;
	int			mFD;
	int			mPort;
	std::string	mPass;
	std::string mName;
	Database	mDB;
	std::string mServerName;
	sockaddr_in		mSockAddr;
	
public:
	explicit Connector(int port, const std::string& pass, time_t timeout); // HASH THE PWD
	void operator()();
																		  // think about the timeout
	~Connector();
private:
	bool createSocket();
	bool bindSocket();
	bool listenSocket();
	void deleteSocket();

	struct pollfd acceptConnection();
	User* registerUser(const struct pollfd& pfd);
	void listenConnection();

	bool checkConnection();
};
