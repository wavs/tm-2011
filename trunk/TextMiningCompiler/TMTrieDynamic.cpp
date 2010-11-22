/*
 *  TMTrieDynamic.cpp
 *  TextMiningCompiler
 *
 *  Created by pierre on 11/22/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "TMTrieDynamic.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <new>
#include <stdio.h>


TrieDynamic::TrieDynamic(std::string &filePath):
	trieRoot(NULL)
{
	this->parseFileToTrie(filePath);
}

TrieDynamic::~TrieDynamic(){
	this->deleteNode(this->trieRoot);
}


void		TrieDynamic::parseFileToTrie(std::string filePath){
	std::fstream		myFileStream;
	std::string			myLine;
	std::istringstream	frequenceWordStr;
	unsigned long int	frequenceWordInt;
	
	myFileStream.open(filePath.c_str(), std::fstream::in);
	
	
	if (myFileStream.is_open())
	{
		
		while ( myFileStream.good() )
		{
			std::getline (myFileStream, myLine);
			std::istringstream iss(myLine);
			std::vector<std::string> tokens;
			
			/* We Could Optimize this*/
			std::copy(std::istream_iterator<std::string>(iss),
					  std::istream_iterator<std::string>(),
					  std::back_inserter<std::vector <std::string> >(tokens));
			
			if (tokens.size() == 2)
			{
				frequenceWordStr.clear();
				frequenceWordStr.str(tokens[1]);
				frequenceWordStr >> frequenceWordInt;
				
				this->trieRoot = this->addWord(this->trieRoot, tokens[0], frequenceWordInt);
#if DEBUG
				std::cout << tokens[0] << "/" << frequenceWordInt << std::endl;
#endif /* DEBUG */
			}
		}
		myFileStream.close();
	}
	else
	{
		std::cerr << "Unable to open file"; 
	}
	
}

s_node		*TrieDynamic::addWord(s_node  *currentNode, std::string word, uint32_t frequence)
{
	s_node *brothers;
	if (word.size() != 0) {
		/* brother -< currentMode */
		brothers = currentNode;
		currentNode = this->getCell(currentNode, word[0]);
		if (currentNode != NULL) {
			if (word.size() == 1) {
				this->setFrequence(currentNode, frequence);
			}
			else {
				currentNode->sons = this->addWord(currentNode->sons, word.substr(1), frequence);
			}
			currentNode->sons = this->addWord(currentNode, word.substr(1), frequence);
			return currentNode;

		}
		else{
			if (word.size() == 1) {
				if (brothers) {
					currentNode = this->addCell(brothers->sons, word[0], frequence);

				}
				else {
					currentNode = this->addCell(NULL, word[0], frequence);
				}

			}
			else {
				if (brothers) {
					currentNode = this->addCell(brothers->sons, word[0], 0);
					
				}
				else {
					currentNode = this->addCell(NULL, word[0], 0);
				}				currentNode->sons = this->addWord(currentNode->sons, word.substr(1), frequence);

			}
			return currentNode;
		}
		
	}
	else {
		return (NULL);
	}

	
#if 0
	
	s_node	*currentCell = this->trieRoot;
	s_node	*tempCell = NULL;
	s_node	*nextCell = this->trieRoot;
	
	int			i;
	
	for (i = 0; i < word.size() - 1; ++i) {
		tempCell = this->getCell(nextCell, word[i]);
		if (currentCell != NULL) {
			nextCell = currentCell->sons;
		}
		else {
			currentCell = this->addCell(nextCell, word[i], 0);
			if ((this->trieRoot == NULL) && (i == 0) ){
				this->trieRoot = currentCell;
			}
			if (!currentCell) return;
			nextCell = currentCell;
		}
	}
	
	currentCell = this->getCell(nextCell, word[i]);
	if (currentCell != NULL) {
		this->setFrequence(currentCell, frequence);
		nextCell = currentCell->sons;
	}
	else {
		currentCell = this->addCell(nextCell, word[i], frequence);
		if (!currentCell) return;
		nextCell = NULL;
	}
#endif / *old addWord* /
}

s_node	*TrieDynamic::addCell(s_node	*currentCell, char	letter, uint32_t frequence){
	
	s_node *newCell = new s_node;
	
	while ((currentCell != NULL) && (currentCell->brother != NULL)) {
		currentCell = currentCell->brother;
	}
	
	
	if (newCell) {
		newCell->brother	= NULL;
		newCell->sons		= NULL;
		newCell->frequence	= frequence;
		newCell->letter		= letter;
		if (currentCell) {
			currentCell->brother = newCell;
		}
	}	
	
	return newCell;
	
}

/* return the node of the letter */
s_node	*TrieDynamic::getCell(s_node	*currentCell, char letter){
	
	while ((currentCell != NULL) && (currentCell->letter != letter)) {
		currentCell = currentCell->brother;
	}	
	return currentCell;
}



void	TrieDynamic::setFrequence(s_node	*currentCell, uint32_t frequence){
	currentCell->frequence = frequence;
}

uint32_t	TrieDynamic::getFrequence(std::string word){
	s_node	*currentCell = NULL;
	s_node	*nextCell = this->trieRoot;

	int			i;
	
	for (i = 0; i < word.size(); ++i) {
		currentCell = this->getCell(nextCell, word[i]);
		if (currentCell != NULL) {
			nextCell = currentCell->sons;
		}
		else {
			nextCell = NULL;
		}

	}
	
	return currentCell->frequence;
}

void		TrieDynamic::deleteNode(s_node	*node)
{
	if (node != NULL) {
		deleteNode(node->brother);
		deleteNode(node->sons);
		delete node;
	}	
	return;	
}


int			TrieDynamic::compileTrie(std::string destinationPath){
/* FIXME */
	return 0;
}


