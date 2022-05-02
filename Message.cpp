#include <iostream>
#include <string>

template <class TMsg>
class Message {
	std::string from;
	std::string to;
	std::string msg;

	TMsg& self() { return *static_cast<TMsg *>(this); }
public:
	static Message<TMsg>* create(const std::string& a, const std::string& b) {
		return new Message<TMsg>(a, b);
	}
	static Message<TMsg>* create(const std::string& a, const std::string& b, const std::string& c) {
		return new Message<TMsg>(a, b, c);
	}
};

struct Nick : public Message<Nick> {
	std::string from;
	std::string msg;

	Nick(const std::string& a, const std::string& b): from(a), msg(b) {}
	Message<Nick>* create(const std::string& a, const std::string& b) { return Message<Nick>::create(a, b); }
};

struct Welcome : public Message<Welcome> {
	std::string from;
	std::string to;
	std::string msg;

	Welcome(const std::string& a, const std::string& b, const std::string& c): from(a), to(b), msg(c)  {}
	Message<Nick>* create(const std::string& a, const std::string& b, const std::string& c) { return Message<Nick>::create(a, b, c); }
};

int main() {
}
