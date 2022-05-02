#include "Connector.hpp"

Connector::Connector(int port, const std::string& pass, time_t timeout)
	: mPort(port),
	mPass(/* hash */ pass)
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

void deleteSocket() {
	// TODO ;)
}
