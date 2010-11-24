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
#include <queue>

#define  Ko_1 1024
#define  Ko_64 65536

TrieDynamic::TrieDynamic(std::string &filePath):
	trieRoot(NULL)
{
	this->parseFileToTrie(filePath);
}

TrieDynamic::TrieDynamic():
	trieRoot(NULL)
{
	
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
			//currentNode->sons = this->addWord(currentNode, word.substr(1), frequence);
			return brothers;

		}
		else{
			if (word.size() == 1) {
				if (brothers) {
					currentNode = this->addCell(brothers, word[0], frequence);

				}
				else {
					currentNode = this->addCell(NULL, word[0], frequence);
					brothers = currentNode;
				}

			}
			else {
				if (brothers) {
					currentNode = this->addCell(brothers, word[0], 0);
					
				}
				else {
					currentNode = this->addCell(NULL, word[0], 0);
					brothers = currentNode;
				}
				currentNode->sons = this->addWord(currentNode->sons, word.substr(1), frequence);

			}
			
			return  brothers;
		}
		
	}
	else {
		return (NULL);
	}
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


int			TrieDynamic::compileTrieToFile(std::string destinationPath){
	/* creating queue here */
	std::queue<s_node *> *file1 = new std::queue<s_node *>;
	std::queue<s_node *> *file2 = new std::queue<s_node *>;
	s_node *brother;
	file1->push(this->trieRoot);
	brother = this->trieRoot;
	
	do {
		
		if (brother) {
			brother = brother->brother;
			file1->push(brother);
		}
		
		
	} while (brother);
	/* initialisation of the outputFile */
	std::ofstream		myFileStream;
	
	myFileStream.open(destinationPath.c_str(), std::fstream::out);
	
	if (myFileStream.is_open())
	{
		while (!file1->empty()) {
			while (!file1->empty()) {
				s_node * x = file1->front();
				file1->pop();
				if ((!x)) { // x == NULL
					if (file1->size() > 0) {
						myFileStream << "/" << std::endl;
					}
				}
				else {
					myFileStream << "?"  << x->letter << ","<< x->frequence;
					brother = x->sons;
					file2->push(brother);
					do {
						
						if (brother) {
							brother = brother->brother;
							file2->push(brother);
						}
						
						
					} while (brother);
				}
				
			}
			delete file1;
			file1 = file2;
			file2 = new std::queue<s_node *>;
			if (!file1->empty()) {
				myFileStream << "%\n";
			}
		}
		myFileStream.close();
	}
	else
	{
		std::cerr << "Unable to open file"; 
	}
	/* free memory */
	delete file2;
	delete file1;
	return 0;
}

/* return 1 if '/' at the end 0 if '%' at the end of line */
int			TrieDynamic::pushMyListWithLine(std::queue<s_node*> *myList, char *line)
{
	std::string myString(line);
	std::string substring;
	std::istringstream frequenceWordStr;
	int					frequenceWordInt;

	int pos1 = 0;
	int pos2 = 0;
	int ending = 0;
	/* exemple of two different lines */
	//#6,705#7,695#8,2014#9,758#a,810#i,69619/
	//#0,5349#1,569#2,763%
	pos1 = myString.find("?", pos1);
	pos2 = myString.find("?", pos1 + 1);
	ending = myString.find("/");
	std::string currentFreq;
	char c;

	while (pos2 > pos1) {
		/* get substring */
		substring = myString.substr(pos1 + 1, pos2 - 1);
		/* decompose substring */
		c = substring.substr(0, substring.find(",")).at(0);
		currentFreq = substring.substr(substring.find(",") + 1);
		frequenceWordStr.clear();
		frequenceWordStr.str(currentFreq);
		frequenceWordStr >> frequenceWordInt;
		/* create s_node* */
		s_node *node = new s_node;
		/* init s_node* */
		node->brother	= NULL;
		node->sons		= NULL;
		node->frequence	= frequenceWordInt;
		node->letter		= c;
		/* push the s_node* */
		myList->push(node);
		/* get new pos1 and pos2 */
		pos1 = myString.find("?", pos2);
		pos2 = myString.find("?", pos1 + 1);
	}
	if (pos1 > pos2)
	{
		substring = myString.substr(pos1 + 1);
		

		c = substring.substr(0, substring.find(",")).at(0);
		currentFreq = substring.substr(substring.find(",") + 1);
		
		frequenceWordStr.clear();
		frequenceWordStr.str(currentFreq);
		frequenceWordStr >> frequenceWordInt;
		s_node *node = new s_node;
		node->brother	= NULL;
		node->sons		= NULL;
		node->frequence	= frequenceWordInt;
		node->letter		= c;
		myList->push(node);
	}
	
	
	if (ending == -1)
		return 1; // maybe we should push a NULL here too.
	else {
		/* we should push a NULL value */
		myList->push(NULL);
	}

	return 0;
}

int			TrieDynamic::importCompiledTrie(std::string filePath)
{
	/* creating queue here */
	std::queue<s_node *>	*file1 = new std::queue<s_node *>;
	std::queue<s_node *>	*file2 = new std::queue<s_node *>;
	std::queue<s_node *>	*file3 = new std::queue<s_node *>;
	/* initialisation of the outputFile */
	std::ifstream			myFileStream;
	s_node *X;
	/* creating the Trie */
	if (this->trieRoot){
		delete this->trieRoot;
		this->trieRoot = NULL;
	}
	
	char					*line = new char[Ko_64];
	
	myFileStream.open(filePath.c_str(), std::fstream::in);
	
	if (myFileStream.is_open())
	{
		/* init the file1 == queue1 */
		memset(line, 0, Ko_64);
		myFileStream.getline(line, Ko_64);
		while (!(this->pushMyListWithLine(file1, line))) {
			memset(line, 0, Ko_64);
			
			myFileStream.getline(line, Ko_64);
		}
		/* recupérer le premier de la file1, ce sera le trieRoot */
		this->trieRoot = file1->front();
		/* on devrait tous les mettres en tant que frere ici */
		std::queue<s_node *> *temp = new std::queue<s_node *>;
		//temp->push(file1->front());
		
		s_node *tempfrere = NULL;
		while (!file1->empty()) {
			tempfrere = file1->front();
			file1->pop();
			temp->push(tempfrere);
			if(!file1->empty())
			{
				tempfrere->brother = file1->front();	
			}
		}
		/* we put the temp in the file1 */
		delete file1;
		file1 = temp;
		
		while (!file1->empty()) {
			/* enfile file2 with le reste jusqu'a % */
			memset(line, 0, Ko_64);

			myFileStream.getline(line, Ko_64);
			while (!(this->pushMyListWithLine(file2, line))) {
				memset(line, 0, Ko_64);

				myFileStream.getline(line, Ko_64);
			}
			/* Creating the Trie again*/
			while (!file1->empty()) {
				X  = file1->front();
				file1->pop();
				if (X){ /* the Node X exist*/
					s_node *Y;
					if (file2->empty())
						Y = NULL;
					else {
						Y = file2->front();
						file2->pop();
						//file3->push(Y);
					}
					X->sons = Y;
					while (Y) { /* !NULL */
						if (file2->empty())
							Y->brother = NULL;
						else {
							Y->brother = file2->front();
							file2->pop();
						}
						if (Y)
							file3->push(Y);
						Y = Y->brother;
					}
				}
			}
			delete file1;
			file1 = file3;
			file3 = new std::queue<s_node *>;
			delete file2;
			file2 = new std::queue<s_node *>;
			
		}
	}
	else
	{
		std::cerr << "Unable to open file"; 
	}
	/* free memory */
	delete file3;
	delete file2;
	delete file1;
	return 0;
	
		
}


s_node*
TrieDynamic::getBrothers()
{
	return this->trieRoot->brother;
}

s_node*
TrieDynamic::getSons()
{
	return this->trieRoot->sons;
}

char
TrieDynamic::getLetter()
{
	return this->trieRoot->letter;
}

uint32_t
TrieDynamic::getNodeFrequence()
{
	return this->trieRoot->frequence;
}

s_node*
TrieDynamic::getTrieRoot()
{
	return this->trieRoot;
}

void
TrieDynamic::setTrieRoot(s_node* trieRoot)
{
	this->trieRoot = trieRoot;
}

void
TrieDynamic::printTrie(s_node* node, int space)
{
	if (node != NULL)
	{
		for (int i = 0; i < space; i++)
			std::cout << " ";
		std::cout << node->letter << " " << node->frequence << " floor : " << space << std::endl;
		this->printTrie(node->brother, space+1);
		this->printTrie(node->sons, space+1);
	}
}

