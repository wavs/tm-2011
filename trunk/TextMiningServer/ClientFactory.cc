/**
 ** \file ClientFactory.cc
 ** \author Thomas Ait-taleb
 ** \version 0.1
 ** \date 19 novembre 2010
 ** \brief Implémentation de la classe ClientFactory
 **/

#include "ClientFactory.hh"

ClientFactory::ClientFactory ()
{
	_client_unique_id = 0;
}

ClientFactory::~ClientFactory ()
{}

Client
*ClientFactory::createClientInstance(int sock, sockaddr_in	*addr)
{
	++_client_unique_id;
	Client	*newClient = new Client(_client_unique_id, sock, addr);
	
	return newClient;
}