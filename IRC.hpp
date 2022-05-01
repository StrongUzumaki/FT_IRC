#pragma		once
#include	"Server.hpp"

class IRC {
	public:
		IRC(int ac, char **av);
		IRC(IRC & src);
		IRC & operator=(IRC & src);
		void operator()();
		~IRC();
	private:
		void createServer();
		enum mErrors {
			wrongNumberofArgs,
			wrongPort	
		};
		void ErrorHandler(mErrors const & Error);
		Server mServer;
};
