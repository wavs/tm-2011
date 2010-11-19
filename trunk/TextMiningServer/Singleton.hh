/*!
 *	\file Singleton.hh
 *	\author Thomas Ait-taleb
 *	\version 0.1
 *	\date 17 novembre 2010
 *	\brief Déclaration de la classe templatée Singleton
 */

#ifndef SINGLETON_HH
# define SINGLETON_HH

# include <iostream>

/*!
 *	\class DataManager
 *	\brief Classe représentant le gestionnaire de données.
 *
 *  La classe gère le chargement, le stockage et le dumpage
 *	des données.
 */
template <typename T>
class Singleton {
	
protected:
	
	static T	*_singleton;	/*!< Singleton */
	
	/*!
	 *	\brief Constructeur de la classe DataManager
	 */
	Singleton() {}
	
	/*!
	 *	\brief Destructeur de la classe DataManager
	 */
	~Singleton() {}
	
public:
	
	/*!
	 *	\brief Instanceur de la classe DataManager
	 */
	static T	*getInstance()
	{
		if (_singleton == NULL)
			_singleton = new T;
		
		return static_cast<T*>(_singleton);
	}
	
	/*!
	 *	\brief Destructeur de l'unique instance de la classe DataManager
	 */
	static void killInstance()
	{
		if (_singleton != NULL)
		{
			delete _singleton;
			_singleton = NULL;
		}
	}	
};

template <typename T>
T *Singleton<T>::_singleton = NULL;

#endif // !SINGLETON_HH
