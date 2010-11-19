/*!
 *	\file Client.hh
 *	\author Thomas Ait-taleb
 *	\version 0.1
 *	\date 19 novembre 2010
 *	\brief Déclaration de la classe Client
 */

#ifndef CLIENT_HH
# define CLIENT_HH

using namespace std;

# include <netinet/in.h>
# include <string>
# include <iostream>

/*!
 *	\class Client
 *	\brief Classe représentant un client
 *
 *  La classe gère la création des clients à identifiant unique.
 */
class Client {
	
private:
	
	int			identifier;		/*!< Identifiant unique du client. */
	int			clientSocket;	/*!< Socket du client. */
	sockaddr_in	*clientAddr;	/*!< Adresse du client. */
	
	
public:
	
	/*!
	 *	\brief Constructeur de la classe Client
	 */
	Client (int uid, int sock, sockaddr_in	*addr);
	
	/*!
	 *	\brief Destructeur de la classe Client
	 */
	~Client ();
	
	/*!
	 *	\brief Getter de la propriété Identifiant
	 *
	 *	\return retourne l'identifiant unique du client.
	 */
	int getIdentifier();
	
	/*!
	 *	\brief Getter de la propriété Socket
	 *
	 *	\return retourne le socket par lequel le client communique.
	 */
	int getSocket();
	
	/*!
	 *	\brief Getter de la propriété Adresse
	 *
	 *	\return retourne les informations relatives à l'adresse du client.
	 */
	sockaddr_in	*getAddress();
	
	/*!
	 *	\brief Handler des commandes envoyées par les clients connectés
	 */
	int handleCommands(string *command);
};

#endif // !CLIENT_HH
