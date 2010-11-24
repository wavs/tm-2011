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
#include "levenshtein.hh"

#define TESTS 1

void printTrie(s_node* node, int space, char type)
{
	if (node != NULL)
	{
		for (int i = 0; i < space; i++)
			std::cout << " ";
		std::cout << " " << type << " \"" << node->letter << "\" " << node->frequence << " floor : " << space << std::endl;
		printTrie(node->brother, space+1, 'B');
		printTrie(node->sons, space+1, 'S');
	}
}

void usage()
{
	std::cout << "Usage: TextMiningServer port pathOfDataFile" << std::endl;
	std::cout << "       -h      Help" << std::endl;
}

int main (int argc, char * const argv[]) {
	
	
#if TESTS
	
	// Lancement des tests
	DataManager	*dataManager = DataManager::getInstance();
	//dataManager->TEST_exportJSON();
	dataManager->loadFile("/Users/wavs/Desktop/output.txt");
	std::cout << "Tree builded." << std::endl;
	
	//printTrie(dataManager->getTrie()->getTrieRoot(), 0, 'R');
	
	dataManager->TEST_TrieConstruction("/Users/wavs/Desktop/iop.txt", dataManager->getTrie());
	
	int i = 0;
	s_node* root = dataManager->getTrie()->getTrieRoot();
	while (root != NULL) {
		root = root->sons;
		i++;
	}
	
	int j = 0;
	s_node* root2 = dataManager->getTrie()->getTrieRoot();
	while (root2 != NULL) {
		root2 = root2->brother;
		j++;
	}
	
	std::cout << "Profondeur de l'arbre (sons)" << i << std::endl;
	std::cout << "Profondeur de l'arbre (brothers)" << j << std::endl;
	
#else
	
	// Arguments manager
	if (argc > 2)
	{
		// Récupération du numéro de port
		size_t	numPort = atoi(argv[1]);
		
		// Récupération du chemin du fichier de données
		string filePath = string(argv[2]);
		
		// Dictionary loader
		DataManager	*dataManager = DataManager::getInstance();
		dataManager->loadFile(filePath);
	
		// Server initialization
		Server	*server = new Server(numPort);
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
	}
	else
	{
		usage();
		return 1;
	}

#endif
	
    return 0;
}
