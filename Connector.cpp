#include "Connector.hpp"

Connector::Connector(int port, const std::string& pass, time_t timeout = 0)
	:
	mIP(inet_addr("127.0.0.1")),
	mPort(port),
	mPass(/* hash */ pass)
{
	if (!createSocket())
		throw std::runtime_error("Couldn't create a socket:(");
	if (bindSocket())
		throw std::runtime_error(strerror(errno));
	if (listenSocket())
		throw std::runtime_error(strerror(errno));
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

static void reaaad(struct pollfd pfd) {
	char buf[100];
	int bytesRead;
	std::string text;
	while ((bytesRead = recv(pfd.fd, buf, 99, 0)) > 0)
	{
		buf[bytesRead] = 0;
		text += buf;
		buf[0] = 0;
		if (text.find('\n') != std::string::npos)
			break;
	}
	std::cout << text << std::endl;
}

void Connector::listenConnection() {
	int revents = poll((struct pollfd*)mDB.getFDs().data(), mDB.getFDs().size(), 1);
	if (revents > 0) {
		for (size_t i = 0; i < mDB.getUsers().size(); i++) {
			if (mDB.getFd(i).revents & POLLIN) {
				reaaad(mDB.getFd(i));
			}
		}	
	}
}

User*	Connector::registerUser(const struct pollfd& pfd) {
	char host[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &mAddr.sin_addr, host, INET_ADDRSTRLEN);
	return new User(host, mName);
}

