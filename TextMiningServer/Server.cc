/**
 ** \file Server.cc
 ** \author Thomas Ait-taleb
 ** \version 0.1
 ** \date 17 novembre 2010
 ** \brief Implémentation de la classe Server
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
		Client		*currentClient;
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
		
		// Création du client
		ClientFactory	*clientFactory = ClientFactory::getInstance();
		currentClient = clientFactory->createClientInstance(clientSocket, &clientAddr);
		
		// Création du thread spécifique au client
		if (pthread_create(&clientThread, NULL, requestHandler, (void*)currentClient) != 0)
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

# define BUFFER_SIZE 4096

void *requestHandler (void *data)
{
	bool	isConnected = true;
	Client	*client = (Client*)data;

	// Test: affichage du port et de l'adresse IP du client
	std::cout	<< "Client connecté ::  IP : " << inet_ntoa(client->getAddress()->sin_addr)
				<< " ,port = " << ntohs(client->getAddress()->sin_port) << "\n" << std::endl;
	
	while (isConnected)
	{
		std::cout << "Client :: " << client->getIdentifier() << std::endl;
		
		// Réception de la commande
		char buffer[BUFFER_SIZE];
		size_t ret;
		ret = recv(client->getSocket(), buffer, BUFFER_SIZE, 0);
		buffer[ret] = '\0';
		
		// Handling de la commande
		string	*receivedCmd = new string(buffer, ret);
		std::cout << "Received data: " << *receivedCmd << std::endl;
		int status = client->handleCommands(receivedCmd);
		
		// Cas d'une commande exit de la part d'un client
		if (status == 1)
			isConnected = false;
		
		// Free memory
		delete receivedCmd;
	}
	
	// Fermeture du socket de communication
	close(client->getSocket());
	
	// Free memory
	delete client;
	
	// Destruction du thread
	pthread_exit(NULL);
	
	return NULL;
}

