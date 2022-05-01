#include <iostream>

class MainErrorHandler {	
	public:
		enum Errors {
			wrongNumberofArgs,
			wrongPort	
		}
		void HandleError(Errors Error);
}
