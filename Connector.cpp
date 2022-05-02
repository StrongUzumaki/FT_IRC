#include "Connector.hpp"

Connector::Connector(int port, const std::string& pass, time_t timeout)
	: mPort(port),
	mPass(/* hash */ pass),
	mIP(inet_addr("127.0.0.1"))
{
	time_t i;
	for (i = 0; !createSocket() && i < timeout;)
		++i;
	if (i == timeout)
		throw std::runtime_error("Couldn't create a socket:(");
	for (i = 0; !bindSocket() && i < timeout;)
		++i;
	if (i == timeout) {
		deleteSocket();
		throw std::runtime_error("Couldn't bind the socket:(");
	}
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
	bool bound = bind(mFD, (struct sockaddr*)&mAddr, sizeof(sockaddr)) >= 0;
	return bound;
}

bool Connector::listenSocket() {
	return listen(mFD, 128) == 0;
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
	if (connection < 1)
		return pfd;
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

}

User*	Connector::registerUser(const struct pollfd& pfd) {
	char host[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &mAddr.sin_addr, host, INET_ADDRSTRLEN);
	return new User(host, mName);
}

