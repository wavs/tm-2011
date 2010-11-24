/*
 *  TMTrieDynamic.h
 *  TextMiningCompiler
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

typedef struct s_node {
	s_node		*sons;
	s_node		*brother;
	char		letter;
	uint32_t	frequence;
} s_list;

class TrieDynamic {
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
private:
	int			pushMyListWithLine(std::queue<s_node*> *myList, char *line);

public:
	TrieDynamic(std::string &filePath);
	TrieDynamic();
	~TrieDynamic();
public:
	uint32_t	getFrequence(std::string word);
	
	
	
	
	/* Dump the structure char* trie to the file */
	int			compileTrieToFile(std::string destinationPath);
	int			importCompiledTrie(std::string filePath);
	
	s_node*		getBrothers();
	s_node*		getSons();
	uint32_t	getNodeFrequence();
	char		getLetter();
	void		printTrie(s_node* node, int space);
	s_node*		getTrieRoot();
	void		setTrieRoot(s_node* trieRoot);
};
#endif