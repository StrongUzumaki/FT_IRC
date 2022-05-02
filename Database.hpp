#pragma once

#include <vector>
#include <poll.h>
#include "User.hpp"

using std::begin;
using std::end;

typedef std::pair<User *, struct pollfd> UBinding;

class Database {
private:
	std::vector<User *>	mUsers;
	std::vector<struct pollfd> mFds;
public:
	Database() {}
	~Database() {}
	
// getters 
	UBinding getBinding(size_t idx) const {
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
	const std::vector<struct pollfd>& getFDs() const { return mFds; }
	const std::vector<User *> getUsers() const { return mUsers; }

// add/remove user 
	void /* bool? */ addUser(User* user, struct pollfd fd) {
		mUsers.push_back(user);
		mFds.push_back(fd);
	}

	void /* bool? */ addUser(const UBinding& p) {
		return addUser(p.first, p.second);
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

