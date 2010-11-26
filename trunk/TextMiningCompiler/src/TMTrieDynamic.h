/*!
 *  \file TMTrieDynamic.h
 *	\author Pierre Guilbert
 *	\version 1.0
 *  \date 22 novembre 2010
 *  \brief Implémentation du Trie sous forme d'abre général binaire (premier fils gauche frer droit)
 *	TextMiningCompiler
 *
 *  Created by pierre on 11/22/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __TMTRIEDYNAMIC__
# define __TMTRIEDYNAMIC__
# include <map>
# include <iostream>
# include <queue>
# include <stdlib.h>
# include <stdint.h>


/*!
 *	\struct s_node
 *	\brief Un noeud du Trie
 *
 *	sons est un pointeur sur s_node représentant le premier fils
 *  brother est un pointeur sur s_node représentant tout les frères du noeud.
 */
typedef struct s_node {
	s_node		*sons;
	s_node		*brother;
	char		letter;
	uint32_t	frequence;
} s_list;


/*!
 *	\class TrieDynamic
 *	\brief Classe représentant notre structure d'arbre
 *
 *  La classe gère l'initialisation depuis un fichier de type exalead, l'export et import du Trie dans un format spécifique
 */
class TrieDynamic {
private:
	s_node		*trieRoot; /*!< Racine de l'arbre */
	
private:
	/*!
	 *	\param filePath : le fichier contenant les mots et leur fréquence
	 *	\brief Construit le Trie depuis un fichier de type Exalead
	 */
	void		parseFileToTrie(std::string filePath);
	
	/*!
	 *	\brief add a word to the trie with the frequence
	 */
	s_node		*addWord(s_node	*currentNode, std::string word, uint32_t frequence);
	/*!
	 *	\brief append a node to the currentNode's brother list
	 */
	s_node		*addCell(s_node	*currentNode, char letter, uint32_t frequence);
	/*!
	 *	\brief return the s_node with the letter or the NULL pointer in the brother list of
	 *  currentNode
	 */
	s_node		*getCell(s_node	*currentNode, char letter);
	/*!
	 *	\brief delete a node and his sons and brother recursively
	 */
	void		deleteNode(s_node *);
	/*!
	 *	\brief Set Frequence of a node
	 */
	void		setFrequence(s_node	*currentCell, uint32_t frequence);
private:
	/*!
	 *	\brief The idea is to get a line in the compiled file
	 * Which is in the format ?value,frequence?value,frequence
	 *  \// if we change of father
	 *  and % if we change of level
	 */
	int			pushMyListWithLine(std::queue<s_node*> *myList, char *line);

public:
	/*!
	 * \brief Construct directly the Trie from file at initialization
	 */
	TrieDynamic(std::string &filePath);
	TrieDynamic();
	/*!
	 ** \brief Destructor called the deleteNode method and free all allocated memory
	 */
	~TrieDynamic();
public:
	uint32_t	getFrequence(std::string word);
	
	
	
	
	
	/*!
	 * Dump the structure char* trie to the file in parameter
	 */
	int			compileTrieToFile(std::string destinationPath);
	/*!
	 * \brief create a Trie from the compiled file
	 *  We should have call the Constructor()
	 */
	int			importCompiledTrie(std::string filePath);
	
	
	/*! \brief get brothers of the root
	 */
	s_node*		getBrothers();
	/*!
	** \brief get the sons of the root
	 */
	s_node*		getSons();
	/*!
	 * \brief get the frequence of the root
	 */
	uint32_t	getNodeFrequence();
	
	/*! \brief get the letter of the root
	 **/
	char		getLetter();
	/*!
	 \brief print the TRIE
	 */
	void		printTrie(s_node* node, int space);
	/*!
	 \brief return the trieRoot
	 */
	s_node*		getTrieRoot();
	/*!
	 *  \brief set our Trie Root
	 */
	void		setTrieRoot(s_node* trieRoot);
};
#endif