#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

class Server {
	
	public:
		Server();
		Server(Server const & src);
		Server & operator=(Server const & src);
		~Server();
		void createSocket();
		void bindSocket();
		void deleteSocket();


	private:
		sockaddr_in mSockAddr;
		int 		mSockFd;

};
