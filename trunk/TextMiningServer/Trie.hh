/*!
 *	\file Trie.hh
 *	\author Pierre Guilbert
 *	\version 0.1
 *	\date 23 novembre 2010
 *	\brief Déclaration de la classe Trie
 */


#ifndef TRIE_HH
# define TRIE_HH

# include <map>
# include <iostream>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <iterator>
# include <iostream>
# include <vector>
# include <new>
# include <stdio.h>
# include <queue>

/*!
 *	\struct s_node
 *	\brief Noeud de l'arbre Trie
 *
 *	s_node représente la structure contenant le Trie.
 */
typedef struct s_node
{
	s_node		*sons;		/*!< Fils du noeud courant. */
	s_node		*brother;	/*!< Frère du noeud courant. */
	char		letter;		/*!< Lettre représentée par le noeud courant. */
	uint32_t	frequence;	/*!< Fréquence du mot précédemment construit jusqu'à ce noeud. */
};

class Trie {
	
private:
	s_node		*trieRoot;
	
private:
	
	void		parseFileToTrie(std::string filePath);
	/* add a word to the trie with the frequence */
	s_node		*addWord(s_node	*currentNode, std::string word, uint32_t frequence);
	s_node		*addCell(s_node	*currentNode, char letter, uint32_t frequence);
	s_node		*getCell(s_node	*currentNode, char letter);
	void		deleteNode(s_node *);
	void		setFrequence(s_node	*currentCell, uint32_t frequence);
	
public:
	
	Trie(std::string &filePath);
	~Trie();

public:
	
	uint32_t	getFrequence(std::string word);
	/* Dump the structure char* trie to the file */
	int			compileTrie(std::string destinationPath);
	s_node*		getBrothers();
	s_node*		getSons();
	uint32_t	getNodeFrequence();
	char		getLetter();
	void		printTrie(s_node* node, int space);
	s_node*		getTrieRoot();
	void		setTrieRoot(s_node* trieRoot);
};

#endif // !TRIE_HH
