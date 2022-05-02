#pragma once

// socket system
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h> 

// c++
#include <string>
#include <vector>

// FIXME
#include <iostream>

using std::begin;
using std::end;

class User;

class Database {
private:
	std::vector<User *>	mUsers;
	std::vector<struct pollfd> mFds;
public:
	Database() {}
	~Database() {}
	
// getters 
	std::pair<User *, struct pollfd> getPair(size_t idx) const {
		User* user = mUsers.at(idx);
		struct pollfd fd = mFds.at(idx);
		return std::make_pair(user, fd);
	}

	User* getUser(size_t idx) const {
		return mUsers.at(idx);
	}

	struct pollfd getFd(size_t idx) const {
		return mFds.at(idx);
	}

// add/remove user 
	void /* bool? */ addUser(User* user, struct pollfd fd) {
		mUsers.push_back(user);
		mFds.push_back(fd);
	}

	void /* bool? */ removeUser(size_t idx) {
		if (idx > mUsers.size())
			return; // throw ?
		mUsers.erase(begin(mUsers) + idx);
		mFds.erase(begin(mFds) + idx);
	}
	void /* bool? */ removeUser(const User* user) {
		const std::vector<User *>::iterator it = std::find(begin(mUsers), end(mUsers), user);
		if (it == end(mUsers))
			return; // throw ?
		size_t offset = std::distance(begin(mUsers), it);
		mUsers.erase(it);
		mFds.erase(begin(mFds) + offset);
	}

private: // deleted a-la c++98
	Database(const Database& other);
	Database& operator= (const Database& other);
};

class Connector {
};

class IRC {
private:
	Connector connector;
	Database database;
public:
	// just some thoughts
	bool connect(/* ... */); // creates an instance of Connector
							// RAII: if Connector ctor succeeded, we've got an established server

	bool monitor(/* ... */); // listens to incoming events,
							// opens and closes connections to end users

	bool receive(/* ... */); // should this be a separate method?
							// saves connections to database
						   // receives data from connections

	bool send(/* ... */); // sends data to connections

	// ...
	
	IRC() {} // RAII !

};

