/*
 *  TMtrie.cpp
 *  TextMiningCompiler
 *
 *  Created by pierre on 11/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <new>
#include <stdio.h>
#include "TMtrie.h"

void		Trie::initTrieMemory(unsigned long int sizeNeeded)
{
	this->trie = new char[sizeNeeded];
}

void		Trie::initTrieHeaderWithAlphabet(AlphabetMap alphaMap)
{
	
}

void		Trie::resizeTrieMemory(void)
{
	
}

void		Trie::addWord(std::string word, unsigned long int frequence)
{
	std::cout << word << " // " <<frequence<<std::endl;	
}

void		Trie::parseFileToTrie(std::string filePath)
{
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
				
				this->addWord(tokens[0], frequenceWordInt);
			}
		}
		myFileStream.close();
	}
	else
	{
		std::cerr << "Unable to open file"; 
	}
	
}

Trie::Trie(unsigned long int sizeNeeded, AlphabetMap &alphaMap, std::string &filePath):
	trie(NULL)
{
	this->initTrieMemory(sizeNeeded);
	this->initTrieHeaderWithAlphabet(alphaMap);
	this->parseFileToTrie(filePath);
}

Trie::~Trie()
{
	if (this->trie)
	{
		delete[] this->trie;
	}
}


int			Trie::getFrequence(std::string word)
{
	return 0;
}


int			Trie::compileTrie(std::string destinationPath)
{
	return 0;
}
