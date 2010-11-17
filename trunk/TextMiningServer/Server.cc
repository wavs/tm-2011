/**
 ** \file Server.cc
 ** \author Thomas Ait-taleb
 ** \version 0.1
 ** \date 17 novembre 2010
 ** \brief Implementation of Server class
 **/

#include "Server.hh"

Server::Server (int no_port)
{
	port	= no_port;
	state	= Uninitialized;
}

Server::~Server ()
{}

void Server::initialize ()
{
	// Initialisation de la structure contenant les informations
	// relatives à l'adresse du serveur.
	bzero(&serverAddr,sizeof(serverAddr));
	serverAddr.sin_port = htons(port);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// Mise à jour du statut du serveur
	state = Stopped;
}

int Server::start ()
{
	// Création de la socket d'écoute
	if ( (listeningSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
		std::cout << "ERROR: listeningSocket creation." << std::endl;
		return 1;
	}
	
	// On relie la socket d'écoute avec l'adresse du serveur
	if ( bind(listeningSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0 )
	{
		std::cout << "ERROR: listeningSocket binding." << std::endl;
		close(listeningSocket);
		return 1;
	}
	
	// Ecoute sur la socket
	if ( listen(listeningSocket, 10) != 0 )
	{
		std::cout << "ERROR: listeningSocket listenning." << std::endl;
		close(listeningSocket);
		return 1;
	}
	
	// Mise à jour du statut du serveur
	state = Running;
	
	// Serveur runloop
	while (state == Running)
	{
		sockaddr_in	clientAddr;
		int			clientSocket;
		pthread_t	clientThread;
		socklen_t	lenClientAddr = sizeof(clientAddr);
		
		// Connexion entrante d'un nouveau client
		if ( (clientSocket = accept(listeningSocket, (struct sockaddr *)&clientAddr, &lenClientAddr)) == -1 )
		{
			std::cout << "ERROR: clientSocket accepting." << std::endl;
			close(listeningSocket);
			return 1;
		}
		
		// Log client informations
		//std::cout	<< "Client connecté ::  IP : " << inet_ntoa(clientAddr.sin_addr)
		//			<< " ,port = " << ntohs(clientAddr.sin_port) << std::endl;
		
		// Création du thread spécifique au client
		if (pthread_create(&clientThread, NULL, requestHandler, (void*)&clientAddr) != 0)
		{
			std::cout << "ERROR: client thread creation." << std::endl;
			close(listeningSocket);
			return 1;
		}
		
	}
	
	return 0;
}

void Server::pause ()
{}

void Server::stop ()
{}

void *requestHandler (void *data)
{
	sockaddr_in	*clientAddr = (sockaddr_in*)data;

	// Test: affichage du port et de l'adresse IP du client
	std::cout	<< "Client connecté ::  IP : " << inet_ntoa(clientAddr->sin_addr)
				<< " ,port = " << ntohs(clientAddr->sin_port) << "\n" << std::endl;
	
	return NULL;
}

