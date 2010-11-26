/*
 *  evenshtein.h
 *  TextMiningServer
 *
 *  Created by Alex on 23/11/10.
 *  Copyright 2010 Epita. All rights reserved.
 *
 */
#ifndef __LEVEN__
# define __LEVEN__
# include <iostream>

/*!
 *	\param string1 : mot 1, string 2 : mot2
 *	\brief retourne la valeur de distance entre les mots 1 et 2 
 *	suivant l'algorithme de Damereau Levensthein
 */
int distanceLeven(std::string str1, std::string str2);

/*!
 *	\param int v1, int v2 : les valeurs à comparer
 *	\brief retourne la minimum des deux valeurs
 */

int min(int v1, int v2);

#endif