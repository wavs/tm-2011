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

#define DEBUG 0
#define NOT_DEBUG 0

/*** TRIE CLASS IMPLEMENTATION*/
void		Trie::initTrieMemory(uint32_t sizeNeeded)
{
	this->trieMemoryChunk = calloc(sizeNeeded, sizeof(char));
	if (this->trieMemoryChunk)
	{
		this->header = (s_header*) this->trieMemoryChunk;
		this->trieRoot = (uint32_t*) (this->header + 1);
		
		// debug
#if DEBUG
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
	this->cellSize = sizeof(uint32_t)*(this->header->alphabetSize + 1);
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

void		Trie::addWord(std::string word, uint32_t frequence)
{
	uint32_t	*currentCell = this->trieRoot;
	uint32_t		*currentGetCell = NULL;
	int i;
	
	for (i = 0; i < word.size() - 1; ++i) {
		/* check if the cell didn't already exist */
		currentGetCell = this->getCell(currentCell, word[i]);
		if (currentGetCell == NULL) {
			currentCell = this->addCell(currentCell, word[i], 0);
			if (currentCell == NULL){
				/* We should avoid this behavior w/ a proper error handling*/
				return;
			}
		}
		else {
			currentCell = currentGetCell;
		}

#if NOT_DEBUG
		std::cout << "at depth: " << i << "/ with letter: " << word[i] << "/ with frequence" << *(int32_t*)currentCell << std::endl;
#endif /* DEBUG */
	}
	currentGetCell = this->getCell(currentCell, word[i]);
	if (currentGetCell == NULL) {
		currentCell = this->addCell(currentCell, word[i], frequence);
	}
	else {
		
		this->setFrequence(currentGetCell, frequence);
	}
#if NOT_DEBUG
	std::cout << "at depth: " << i << "/ with letter: " << word[i] << "/ with frequence" << *(int32_t*)currentCell << std::endl;
#endif /* DEBUG */
	
	//	std::cout << word << " // " <<frequence<<std::endl;	 /* FIXME */
}

void		Trie::parseFileToTrie(std::string filePath){
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

Trie::Trie(unsigned long int sizeNeeded, AlphabetMap &alphaMap, std::string &filePath):
	trieMemoryChunk(NULL), trieRoot(NULL), header(NULL), maxSizeTrie(sizeNeeded){
	this->initTrieMemory(sizeNeeded);
	this->initTrieHeaderWithAlphabet(alphaMap);
	this->parseFileToTrie(filePath);
}

/* TODO: Create new constructor for direct import from binary file via mmap and stuff */

Trie::~Trie(){
	if (this->trieMemoryChunk)
	{
		free(this->trieMemoryChunk);
	}
}

void	Trie::setHeaderMapping(std::vector<char> *_mapping){
	std::vector<char>::iterator it;
	int count = 0;
	
	for ( it= _mapping->begin() ; it != _mapping->end(); it++ )
	{
		this->header->mapping[count] = *it;	
		count++;
	}	
}

void	Trie::setHeaderAlphabet(std::set<char> &_alphabet){
	std::set<char>::iterator it;
	int count = 0;
	
	for ( it= _alphabet.begin() ; it != _alphabet.end(); it++ )
	{
		this->header->alphabet[count] = *it;
		count++;
	}
}

void	Trie::setHeaderTrieSize(unsigned long int _trieSize){
	this->header->trieSize = _trieSize;
}


uint32_t	Trie::getSpecialPosition(uint32_t *currentCell, char letter){
	
	uint32_t positionCell = 0;
	
	positionCell = currentCell[(int)(this->header->mapping[letter])];
	return positionCell;
}

uint32_t	*Trie::addCell(uint32_t	*currentCell, char	letter, uint32_t frequence){
	/* we check if we have enough memory*/
	if (((this->header->trieSize + 1)*this->cellSize) > this->maxSizeTrie) {
		return NULL;
	}
	/* we set the cell to the letter*/
	uint32_t newsize = this->header->trieSize + 1;
	
	uint32_t *specialPointer = (uint32_t*)&(currentCell[((int)this->header->mapping[letter] + 1)*sizeof(int32_t)]);
	*specialPointer = newsize; // we put a int32_t inside
	/* we put the frequence in the new cell*/
	this->setHeaderTrieSize(this->header->trieSize + 1);
	
	uint32_t	*newCell = this->trieRoot + this->header->trieSize*(sizeof(int32_t)*(this->header->alphabetSize + 1));
	if (frequence != 0) {
		((int32_t*)newCell)[0] = frequence;
	}
	
	return newCell;

}

uint32_t	*Trie::getCell(uint32_t	*currentCell, char letter){
	uint32_t positionCell = *((uint32_t*)&(currentCell[((int)this->header->mapping[letter] + 1)*sizeof(int32_t)]));
	if (positionCell == 0) {
		return NULL;
	}
	else {
		std::cout << "position: " << positionCell << "/ cell for letter: " << letter<< std::endl;
		return this->trieRoot + positionCell*(sizeof(int32_t)*(this->header->alphabetSize + 1));
	}

}

uint32_t	Trie::getFrequence(std::string word){
	uint32_t	*currentCell = this->trieRoot;
	int			i;
	uint32_t	positionLetter;
	
	for (i = 0; i < word.size(); ++i) {
		positionLetter = currentCell[sizeof(int32_t) + this->header->mapping[word[i]]];
		currentCell = this->trieRoot + (positionLetter*this->cellSize);
#if NOTDEBUG
		std::cout << "SEARCHING: at depth: " << i << "/ with letter: " << word[i] << "/ with frequence" << *(uint32_t*)currentCell << std::endl;
#endif /* DEBUG */
	}
	
	return *((uint32_t*)currentCell);
}

void	Trie::setFrequence(uint32_t	*currentCell, uint32_t frequence){
		((uint32_t*)currentCell)[0] = frequence;
}
int		Trie::compileTrie(std::string destinationPath){
	std::ofstream		myFileStream;
	
	myFileStream.open(destinationPath.c_str(), std::fstream::binary | std::fstream::out);
	
	
	if (myFileStream.is_open())
	{
		uint32_t sizeMemory = (this->header->trieSize * this->cellSize) + sizeof(s_header);
		myFileStream.write((char*)this->trieMemoryChunk, sizeMemory );
		myFileStream.close();
	}
	else
	{
		std::cerr << "Unable to open file"; 
	}
	return 0;
}
