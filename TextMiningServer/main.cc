/**
 ** \file main.cc
 ** \author Thomas Ait-taleb
 ** \version 0.1
 ** \date 17 novembre 2010
 ** \brief Start point of the server
 **/

#include <iostream>
#include "Server.hh"
#include "DataManager.hh"

#define TESTS 0

int main (int argc, char * const argv[]) {

#if TESTS
	
	// Lancement des tests
	DataManager	*dataManager = DataManager::getInstance();
	dataManager->TEST_exportJSON();
	
#else
	
	// Arguments manager
	
	// Dictionary loader
	
	// Server initialization
	Server	*server = new Server(2342);
	server->initialize();
	
	// Server runloop
	if ( server->start() == 1)
	{
		std::cout << "ERROR: server couldn't start." << std::endl;
		delete server;
		return 1;
	}
	
	// Free memory
	delete server;
	
#endif
	
    return 0;
}

void usage()
{
	printf("Usage: TextMiningServer port repertoryOfDataFile\n\n");
	printf("       -h      Help\n");
}