/*
 *  serializer.h
 *  TextMiningCompiler
 *
 *  Created by Alex on 23/11/10.
 *  Copyright 2010 Epita. All rights reserved.
 *
 */
#ifndef __SERIALIZER__
# define __SERIALIZER__
# include <iostream>
# include "TMTrieDynamic.h"


/*!
 *	\class Serializer
 *	\brief Classe permettant d'écrire la structure dans un fichier
 *
 * Ecrit dans un format spécifique la structure de donnée de Trie passé en paramètre du constructeur
 * Cette classe fait également l'inverse, cad créer un Trie depuis un fichier
 */
class Serializer
{
private:
	TrieDynamic	*abr; /*!< Trie qui sera traité */
	std::string		fileOut; /*!< fichier de sortie */
	std::string		fileIn; /*!< fichier d'entré */

public:
	/*!
	 *	\param TrieDynamic : Le Trie qui va être sérialiser
	 *	\brief Construit le sérializer
	 */
	
	Serializer(TrieDynamic *abr);

	/*!
	 *	\param none
	 *	\brief Détruit le sérializer
	 */
	~Serializer();

	/*!
	 *	\param string : ecrit la strutre dans un fichier
	 *	\brief Ecrit un format représentant la structure dans le fichier passé en paramètre.
	 */	
	void			writeInFile(std::string fileOut);
	
	/*!
	 *	\param string : le fichier contenant la struture sérialisé
	 *	\brief Construit le Trie depuis un fichier en respectant la lecture du format
	 */
	TrieDynamic*	readFromFile(std::string fileIn);
	
	/*!
	 *	\param string
	 *	\brief change le paramètre fileOut de l'objet
	 */
	void			setFileOut(std::string fileOut);
	/*!
	 *	\param string
	 *	\brief change le paramètre fileIn de l'objet
	 */
	void			setFileIn(std::string fileIn);
	
	/*!
	 *	\param TrieDynamic
	 *	\brief change le paramètre abr de l'objet
	 */
	void			setAbr(TrieDynamic *abr);
	
	/*!
	 *	\param none
	 *	\brief retourne le paramètre fileOut de l'objet
	 */
	std::string		getFileOut();
	
	/*!
	 *	\param none
	 *	\brief retourne le paramètre fileIn de l'objet
	 */
	std::string		getFileIn();
	
	/*!
	 *	\param none
	 *	\brief retourne le paramètre abr de l'objet
	 */
	TrieDynamic*	getAbr();
};
#endif