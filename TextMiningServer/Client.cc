/**
 ** \file Client.cc
 ** \author Thomas Ait-taleb
 ** \version 0.1
 ** \date 19 novembre 2010
 ** \brief Implémentation de la classe Client
 **/

#include "Client.hh"

Client::Client (int uid, int sock, sockaddr_in	*addr)
{
	identifier = uid;
	clientSocket = sock;
	clientAddr = addr;
}

Client::~Client ()
{}

int
Client::getIdentifier()
{
	return identifier;
}

int
Client::getSocket()
{
	return clientSocket;
}

sockaddr_in
*Client::getAddress()
{
	return clientAddr;
}

int
Client::handleCommands(string *command)
{
	// Commande "approx"
	if ((command->length() > 11) &&
		(command->compare(0, 7, "approx ") == 0) &&
		((command->compare(7, 1, "0") == 0)
		 || (command->compare(7, 1, "1") == 0)
		 || (command->compare(7, 1, "2") == 0)))
	{
		int distance = atoi(command->substr(7, 1).c_str());
		string word = command->substr(9, command->length() - 11);
		
		// DEBUG LOG
		std::cout << "[APPROX COMMAND]" << std::endl;
		std::cout << "	distance = " << distance << std::endl;
		std::cout << "	word = " << word << std::endl;
		
		// Récupération du DataManager
		DataManager	*dataManager = DataManager::getInstance();
		
		// Traitement sur le Trie pour trouver les mots proches
		// du mot recherché
		TResults	*results = dataManager->browseDataWithOptions(word, distance);
		
		// Raffinage des résultats
		results = dataManager->refineResults(results);
		
		// Export JSON
		string jsonedResults = dataManager->exportJSON(results);
		
		// Envoi des résultats au client
		ssize_t n = write(getSocket(), jsonedResults.c_str(), jsonedResults.size());
		
		if (n != jsonedResults.size())
			std::cout << "Error: write results to client" << std::endl;
		
		// Free memory
		int i;
		for(i = 0; i < results->size(); i++)
		{
			s_result *r = results->at(i);
			delete r->word;
			free(r);
		}
		delete results;
		
	} else {
		
		// Commande "exit"
		if (command->compare("exit\r\n") == 0)
		{
			// DEBUG LOG
			std::cout << "[EXIT COMMAND]" << std::endl;
			
			return 1;
		
		} else {
			
			// Commande "dump"
			if (command->compare("dump\r\n") == 0)
			{
				// DEBUG LOG
				std::cout << "[DUMP COMMAND]" << std::endl;
			}
		}
	}
	
	return 0;
}