/*!
 *	\file DataManager.hh
 *	\author Thomas Ait-taleb
 *	\version 0.1
 *	\date 17 novembre 2010
 *	\brief Déclaration de la classe DataManager
 */

#ifndef DATAMANAGER_HH
# define DATAMANAGER_HH

# include <iostream>
# include <string>
# include <map>
# include <vector>
# include "Singleton.hh"

using namespace std;

typedef map<string,string> TResultsDictionnary;

/*!
 *	\struct s_result
 *	\brief Résultat à envoyer au client.
 *
 *	s_result représente la structure contenant un résultat à envoyer
 *	au client.
 */
typedef struct
{
	
	string	*word;	/*!< Mot proche du mot recherché. */
	int		freq;	/*!< Fréquence du mot. */
	int		dist;	/*!< Distance par rapport au mot recherché. */
}
s_result;

/*!
 *	\class DataManager
 *	\brief Classe représentant le gestionnaire de données.
 *
 *  La classe gère le chargement, le stockage et le dumpage
 *	des données.
 */
class DataManager : public Singleton<DataManager> {
	
	friend class Singleton<DataManager>;
	
private:
	
	// Data tree
	// \todo Définir la structure de données utilisée
	//TREE	tree;	/*!< Arbre des données chargées */
	
	/*!
	 *	\brief Constructeur de la classe DataManager
	 */
	DataManager	();
	
	/*!
	 *	\brief Destructeur de la classe DataManager
	 */
	~DataManager ();
	
public:
	
	/*!
	 *	\brief Chargement du fichier de données
	 *	\param filename Nom du fichier où les données sont stockées
	 *
	 *	Méthode responsable du chargement du fichier de données et de
	 *	la création de la structure de données spécifiques (B-Tree,...).
	 */
	void loadFile(string filename);
	
	void dump();
	
	/*!
	 *	\brief Recherche de mots par distance de Levenstein-Damereau
	 *	\param word Mot à chercher
	 *	\param dist Distance maximum de proximité au mot recherché
	 *
	 *	Méthode parcourant l'arbre stockant les données à la recherche
	 *	des mots proches du mot recherché avec une distance de
	 *	Levenstein-Damereau maximum.
	 *
	 *	\return Dictionnaire des résultats
	 */
	TResultsDictionnary *browseDataWithOptions(string word, int dist);
	
	/*!
	 *	\brief Exportation des résultats sous forme JSON
	 *	\param results Résultats de la correction orthographique
	 *
	 *	Méthode parcourant l'ensemble des résultats de correction
	 *	orthographique afin de créer le flux JSON à envoyer au
	 *	client connecté au serveur.
	 *
	 *	\return Flux de sortie contenant le flux JSON
	 */
	ostream&	exportJSON(vector<s_result> *results);
	
};

#endif // !DATAMANAGER_HH
