#include "MainErrorHandler.hpp"
#define FAILURE 1

void MainErrorHandler::HandleError(Errors Error) {
	
	switch (Error) {
		case wrongNumberofArgs:
			std::cerr << "Bruh sound effect #2" << std::endl;
			exit(FAILURE);
		case wrongPort:
			std::cerr  << "Wrong port!" << std::endl;
			exit(FAILURE);
	}
}

