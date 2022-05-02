#include "Connector.hpp"

Connector::Connector(int port, const std::string& pass, time_t timeout)
	: mPort(port),
	mPass(/* hash */ pass),
	mIP(inet_addr("127.0.0.1"))
{

	if (!createSocket())
		throw std::runtime_error("Couldn't create a socket:(");
	if (bindSocket())
		throw std::runtime_error(strerror(errno));
	if (listenSocket())
		throw std::runtime_error(strerror(errno));
	//time_t i;
	//for (i = 0; !createSocket() && i < timeout;)
	//	++i;
	//if (i == timeout)
	//	throw std::runtime_error("Couldn't create a socket:(");
	//if (bind < 0)
	//	throw std::runtime_error("Couldn't bind the socket:(");

	//for (i = 0; !!bindSocket() && i < timeout;)
	//	++i;
	//if (i == timeout) {
	//	deleteSocket();
	//	throw std::runtime_error("Couldn't bind the socket:(");
//	}
}


void Connector::operator()() {

	while(1) {
		acceptConnection();
		listenConnection();
	}
}

Connector::~Connector() {
	deleteSocket();
}

bool Connector::createSocket() {
	mFD = socket(AF_INET, SOCK_STREAM, 0);
	return mFD >= 0; // or some other valid condition
}

bool Connector::bindSocket() {
	mAddr.sin_family = AF_INET;
	mAddr.sin_addr.s_addr = mIP;
	mAddr.sin_port = htons(mPort);
	return bind(mFD, (struct sockaddr*)&mAddr, sizeof(sockaddr));
}

bool Connector::listenSocket() {
	int listen_result = listen(mFD, 128);
	fcntl(mFD, F_SETFL, O_NONBLOCK);
	return listen_result;
}

void Connector::deleteSocket() {
	// TODO ;)
}

struct pollfd Connector::acceptConnection() {
	char	host[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(mSockAddr.sin_addr), host, INET_ADDRSTRLEN);
	struct pollfd pfd = { .fd = 0,
						  .events = 0,
						  .revents = 0
	};
	size_t addrlen = sizeof(mAddr);
	int connection = accept(mFD,
							(struct sockaddr *) &mAddr,
							(socklen_t *) &addrlen
	);
	if (connection < 0) {
		//std::cout << "No connection, errno:" << errno << std::endl;
		return pfd;
	}
	std::cout << "new User connected" << std::endl;
	// char host[INET_ADDRSTRLEN];
	// inet_ntop(AF_INET, &(mAddr.sin_addr), host, INET_ADDRSTRLEN);
	pfd.fd = connection;
	pfd.events = POLLIN;
	pfd.revents = 0;
	mDB.addUser(new User(host, mServerName), pfd);
	return pfd;
}

void Connector::listenConnection() {
	int revents = poll((struct pollfd*)mDB.getFDs().data(), mDB.getFDs().size(), 1);
	if (revents > 0) {
		for (size_t i = 0; i < mDB.getUsers().size(); i++) {
			mMessenger
		}	
	}
}

User*	Connector::registerUser(const struct pollfd& pfd) {
	char host[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &mAddr.sin_addr, host, INET_ADDRSTRLEN);
	return new User(host, mName);
}

