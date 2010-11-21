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

#define DEBUG 14244

/*** TRIE CLASS IMPLEMENTATION*/
void		Trie::initTrieMemory(unsigned long int sizeNeeded)
{
	this->trieMemoryChunk = calloc(sizeNeeded, sizeof(char));
	if (this->trieMemoryChunk)
	{
		this->header = (s_header*) this->trieMemoryChunk;
		this->trieRoot = (char*) (this->header + 1);
		
		// debug
#if NOT_DEBUG
		std::cout << "TrieMemoryChunk pos: " << (void*) this->trieMemoryChunk << std::endl;
		std::cout << "header pos: " << (void*) this->header << std::endl;
		std::cout << "trieRoot pos: " << (void*) this->trieRoot << std::endl;
		std::cout << "sizeof header: " << std::hex << sizeof(s_header)<< std::endl;
#endif // 0
	}
}

void		Trie::initTrieHeaderWithAlphabet(AlphabetMap &alphaMap)
{
	/* [alphabet size][TrieSize (unsigned long int) ][127 char long array containing the mapping of our alphabet][our alphabet] */
	this->header->alphabetSize = alphaMap.getAlphabetSize();
	this->header->trieSize = 0;
	this->setHeaderMapping(alphaMap.getConvertionMap());
	this->setHeaderAlphabet(alphaMap.getAlphabet());
	// debug
#if NOT_DEBUG
	std::cout << "header pos: " << (void*) this->header << std::endl;
	std::cout << "maping pos: " << &this->header->mapping << std::endl;
	std::cout << "alphabet pos: " << &( this->header->alphabet) << std::endl;
	std::cout << "alpha size pos: " << (void*) &(this->header->alphabetSize) << std::endl;
	std::cout << "trieSize pos: " << &(this->header->trieSize) << std::endl;
	std::cout << "size of unsigned long int" << sizeof(unsigned long int) << std::endl;
	std::cout << "trieRoot pos: " << (void*) this->trieRoot << std::endl;
#endif
#if NOT_DEBUG
	std::cout << "alphabetsize: " << this->header->alphabetSize << std::endl;
	std::cout << "triesize: " << this->header->trieSize << std::endl;
	std::cout << "mapping: " << this->header->mapping << std::endl;
	for (int i = 0; i < SIZE_ALPHABET; ++i) {
		std::cout << i << ":" << (int)this->header->mapping[i] << "\n";
	}
	std::cout << std::endl;
	
	std::cout << "alphabet: " << this->header->alphabet << std::endl;
	for (int i = 0; i < SIZE_ALPHABET; ++i) {
		std::cout << i+1 << ":" << (char)this->header->alphabet[i] << "\n";
	}
	std::cout << std::endl;


#endif
	
}

void		Trie::resizeTrieMemory(void)
{
 /* FIXME */
}

void		Trie::addWord(std::string word, unsigned long int frequence)
{
	char	*currentCell = this->trieRoot;
	int i;
	for (i = 0; i < word.size() - 1; ++i) {
		currentCell = this->addCell(currentCell, word[i], 0);
	}
	this->addCell(currentCell, word[i], frequence);
	
	//	std::cout << word << " // " <<frequence<<std::endl;	 /* FIXME */
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
	trieMemoryChunk(NULL), trieRoot(NULL), header(NULL)
{
	this->initTrieMemory(sizeNeeded);
	this->initTrieHeaderWithAlphabet(alphaMap);
	this->parseFileToTrie(filePath);
}

/* TODO: Create new constructor for direct import from binary file via mmap and stuff */

Trie::~Trie()
{
	if (this->trieMemoryChunk)
	{
		free(this->trieMemoryChunk);
	}
}


void	Trie::setHeaderMapping(std::vector<char> *_mapping)
{
	std::vector<char>::iterator it;
	int count = 0;
	
	for ( it= _mapping->begin() ; it != _mapping->end(); it++ )
	{
		this->header->mapping[count] = *it;	
		count++;
	}	
}

void	Trie::setHeaderAlphabet(std::set<char> &_alphabet)
{
	std::set<char>::iterator it;
	int count = 0;
	
	for ( it= _alphabet.begin() ; it != _alphabet.end(); it++ )
	{
		this->header->alphabet[count] = *it;
		count++;
	}
}

void	Trie::setHeaderTrieSize(unsigned long int _trieSize)
{
	this->header->trieSize = _trieSize;
}

char	*Trie::addCell(char	*currentCell, char	letter, int32_t frequence)
{
	/* we set the cell to the letter*/
	currentCell[sizeof(int32_t) + this->header->mapping[letter]] = this->header->trieSize + 1;
	/* we put the frequence in the new cell*/
	this->setHeaderTrieSize(this->header->trieSize + 1);
	char	*newCell = this->trieRoot + this->header->trieSize*(sizeof(int32_t)*(this->header->alphabetSize + 1));
	((int32_t*)newCell)[0] = frequence;
	
	return ((char*)newCell);

}

int32_t			Trie::getFrequence(std::string word)
{
	return 0; /* FIXME */
}


int			Trie::compileTrie(std::string destinationPath)
{
	return 0; /* FIXME */
}
