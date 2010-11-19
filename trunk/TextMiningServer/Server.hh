/*!
 *	\file Server.hh
 *	\author Thomas Ait-taleb
 *	\version 0.1
 *	\date 17 novembre 2010
 *	\brief Déclaration de la classe Server
 */

#ifndef SERVER_HH
# define SERVER_HH

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <signal.h>
# include <string>
# include <iostream>
# include <pthread.h>

# include "Client.hh"
# include "ClientFactory.hh"

/*!
 *	\enum e_serverState
 *	\brief Statuts du serveur.
 *
 *	e_serverState est une série de constantes prédéfinies pour représenter les
 *	différents statuts courants du serveur.
 */
typedef enum
{	
	Uninitialized,	/*!< Serveur non initialisé. */
	Running,		/*!< Serveur en cours de fonctionnement. */
	Standby,		/*!< Serveur en pause. */
	Stopped			/*!< Serveur à l'arrêt. */
}
e_serverState;


/*!
 *	\brief Gestion des requêtes client
 *
 *	Méthode s'occupant de gérer les requêtes effectuées par les clients connectés.
 */
void	*requestHandler(void *data);


/*!
 *	\class Server
 *	\brief Classe représentant le serveur
 *
 *  La classe gère l'initialisation, le démarrage, la mise en pause
 *	ainsi que l'arrêt du serveur.
 */
class Server {
	
private:
	
	int				port;				/*!< Numéro du port d'écoute */
	e_serverState	state;				/*!< État courant du serveur */
	sockaddr_in		serverAddr;			/*!< Adresse du server */
	int				listeningSocket;	/*!< Socket d'écoute */
	
	
public:
	
	/*!
	 *	\brief Constructeur de la classe Server
	 *	\param no_port : numéro du port d'écoute initial
	 */
	Server (int no_port);
	
	/*!
	 *	\brief Destructeur de la classe Server
	 */
	~Server ();
	
	/*!
	 *	\brief Initialisation du serveur
	 *
	 *	Méthode initialisant les paramètres principaux
	 *	du serveur.
	 */
	void	initialize();
	
	/*!
	 *	\brief Démarrage du serveur
	 *
	 *	Méthode démarrant le serveur en écoutant sur le port
	 *	les connexions entrantes.
	 */
	int	start();
	
	/*!
	 *	\brief Mise en pause du serveur
	 *
	 *	Méthode mettant en pause le serveur et libérant par
	 *	conséquent le port d'écoute.
	 */
	void	pause();
	
	/*!
	 *	\brief Arrêt du serveur
	 *
	 *	Méthode arrêtant le fonctionnement du serveur.
	 */
	void	stop();
};

#endif // !SERVER_HH
