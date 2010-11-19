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