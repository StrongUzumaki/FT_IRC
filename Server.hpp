#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

class Server {
	private:
		enum mErrors {
			createSocketError,
			bindError,
			listenSocketError
		};
		void handleError(mErrors Error);
		sockaddr_in mSockAddr;
		int 		mSockFd;
		int			mPort;
		in_addr_t	mIP;
	
	public:
		Server();
		Server(Server const & src);
		Server & operator=(Server const & src);
		~Server();
		void createSocket();
		void bindSocket();
		void listenSocket();
		void acceptConnection(); 
		void deleteSocket();

};
