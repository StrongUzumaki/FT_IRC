#pragma once

#include "Database.hpp"
#include "Connector.hpp"

// FIXME
#include <iostream>

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

