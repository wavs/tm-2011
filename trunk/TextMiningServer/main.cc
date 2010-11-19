/**
 ** \file main.cc
 ** \author Thomas Ait-taleb
 ** \version 0.1
 ** \date 17 novembre 2010
 ** \brief Start point of the server
 **/

#include <iostream>
#include "Server.hh"

int main (int argc, char * const argv[]) {

	// Arguments manager
	
	// Dictionary loader
	
	// Server initialization
	Server	*server = new Server(2342);
	server->initialize();
	if ( server->start() == 1)
	{
		std::cout << "ERROR: server couldn't start." << std::endl;
		delete server;
		return 1;
	}
	
	// Server runloop
	
	// Free memory
	delete server;
	
    return 0;
}

void usage()
{
	printf("Usage: TextMiningServer port repertoryOfDataFile\n\n");
	printf("       -h      Help\n");
}