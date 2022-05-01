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
#include <arpa/inet.h>
#include <poll.h>
#include <vector>

#include "User.hpp"

class UserDB {
private:
	std::vector<User *> mUsers;
	std::vector<struct pollfd> mFDs;
public:
	std::pair<struct pollfd, User *> operator[](int i) {
		return std::make_pair(mFDs[i], mUsers[i]);
	}
	void addUser(struct pollfd fd, const User* user) {
		mFDs.push_back(fd);
		mUsers.push_back(user);
	}
	void removeUser(int fd) {
		std::vector<struct pollfd>::iterator it = std::find(mFDs.begin(), mFDs.end(), fd);
		size_t offset = std::distance(mFDs.begin(), it);
		mFDs.erase(it);
		mUsers.erase(mUsers.begin() + offset);
	}
	const std::vector<struct pollfd>& getFDs() const { return mFDs; }
	const std::vector<User *> getUsers() const { return mUsers; }
	size_t size() const { return mUsers.size(); }

	struct pollfd getFD(int i) const { return mFDs[i]; }
	User* getUser(int i) const { return mUsers[i]; }
};

class Server {
<<<<<<< HEAD
=======
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
	
>>>>>>> 22f2647277a9c07bfa713cc6c298925d50a60ba6
	public:
		Server(int port, std::string password);
		~Server();
		void operator()();
	private:
		void	createSocket();
		void	bindSocket();
		void	listenSocket();
		void	acceptConnection(); 
		void	deleteSocket();
		void 	processMessage();
		void 	checkConnection();
		void 	deleteBrokenConnection();
		void 	deleteEmpyChannel();
		Server();
		Server(Server const & src);
		Server & operator=(Server const & src);
<<<<<<< HEAD
		enum mErrors {
			createSocketError,
			bindError
		};
		void 			fatalError(mErrors Error);
		sockaddr_in		mSockAddr;
		int 			mSockFd;
		int				mPort;
		std::string		mPassword;
		in_addr_t		mIP;
		std::string		mServerName;
		// std::vector<User *> 	mUsers;
		UserDB			mUserDB;

		void readMessage();
		void sendMessage();

		struct pollfd getFD(int i) const { return mUserDB.getFD[i]; }
		User* getUser(int i) const { return mUserDB.getUser[i]; }
=======
		~Server();
		void createSocket();
		void bindSocket();
		void listenSocket();
		void acceptConnection(); 
		void deleteSocket();

>>>>>>> 22f2647277a9c07bfa713cc6c298925d50a60ba6
};
