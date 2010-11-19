/**
 ** \file ClientFactory.cc
 ** \author Thomas Ait-taleb
 ** \version 0.1
 ** \date 19 novembre 2010
 ** \brief Implémentation de la classe ClientFactory
 **/

#include "ClientFactory.hh"

ClientFactory::ClientFactory ()
{}

ClientFactory::~ClientFactory ()
{}

void
ClientFactory::createClientInstance()
{
	// FIXME
	++_client_unique_id;
}