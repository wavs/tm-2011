/*!
 *	\file ClientFactory.hh
 *	\author Thomas Ait-taleb
 *	\version 0.1
 *	\date 19 novembre 2010
 *	\brief Déclaration de la classe ClientFactory
 */

#ifndef CLIENTFACTORY_HH
# define CLIENTFACTORY_HH

# include <netinet/in.h>

# include "Singleton.hh"
# include "Client.hh"

/*!
 *	\class ClientFactory
 *	\brief Classe représentant la fabrique de clients
 *
 *  La classe gère la création des clients à identifiant unique.
 */
class ClientFactory : public Singleton<ClientFactory> {
	
	friend class Singleton<ClientFactory>;
	
private:
	
	int	_client_unique_id;	/*!< Compteur des clients créés */
	
	/*!
	 *	\brief Constructeur de la classe ClientFactory
	 */
	ClientFactory ();
	
	/*!
	 *	\brief Destructeur de la classe ClientFactory
	 */
	~ClientFactory ();
	
public:
	
	/*!
	 *	\brief Créateur de clients
	 */
	Client	*createClientInstance(int sock, sockaddr_in	*addr);
};

#endif // !CLIENTFACTORY_HH
