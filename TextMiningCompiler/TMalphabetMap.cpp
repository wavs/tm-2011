/*
 *  TMalphabetMap.cpp
 *  TextMiningCompiler
 *
 *  Created by pierre on 11/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "TMAlphabetMap.h"


void AlphabetMap::parseFileToAlphabet(std::string path)
{
	std::fstream	myFileStream;
	std::string		myLine;
	
	myFileStream.open(path.c_str(), std::fstream::in);
	
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
				this->addingWordCharToAlphabet(tokens[0]);
			}
		}
		this->convertAlphabetToConvertionMap();
		myFileStream.close();
	}
	else
	{
		std::cerr << "Unable to open file"; 
	}
	
}

void AlphabetMap::addingWordCharToAlphabet(std::string word)
{
	for (int i = 0; i < word.length(); ++i) {
		this->alphabet.insert(word[i]);
	}
}

void AlphabetMap::convertAlphabetToConvertionMap(void)
{
	std::set<char>::iterator it;
	char count = 1; /* because we shall not start at zero (to differentiate with initalisation*/
	
	for ( it=this->alphabet.begin() ; it != this->alphabet.end(); it++ )
	{
		this->convertionMap->at(*it) = count;
		count++;
	}
}

void AlphabetMap::initConvertionMap(void)

{
	this->convertionMap = new std::vector<char> (ALPHABET_SIZE_MAX, 0);
}

AlphabetMap::AlphabetMap(std::string path)
{
	this->initConvertionMap();
	this->parseFileToAlphabet(path);
}

AlphabetMap::~AlphabetMap()
{
	delete this->convertionMap;
}

void AlphabetMap::printSizeOfProperties(void)
{
	if (convertionMap)
		std::cout << "convertionMap: "<< this->convertionMap->size() << std::endl;
	std::cout << "alphabet:" << this->alphabet.size() << std::endl;	
}

void AlphabetMap::printAlphabet(void)
{
	std::set<char>::iterator it;
	int count = 0;
	
	std::cout << "Alphabet contains:";
	for ( it=this->alphabet.begin() ; it != this->alphabet.end(); it++ )
	{
		std::cout << " " << *it;
		count++;
	}
	
	std::cout << std::endl;
	std::cout << "of size: " << count << std::endl;
}

void AlphabetMap::printConvertionMap(void)

{
	std::vector<char>::iterator it;
	int count = 0;
	
	std::cout << "ConvertionMap content:" << std::endl;
	for ( it=this->convertionMap->begin() ; it != this->convertionMap->end(); it++ )
	{
		if (*it > 0) {
		std::cout << (char)count << ":" << (int)*it << std::endl;		
		}
	
		count++;
	}	
	std::cout << std::endl;
}

char AlphabetMap::getPosition(char position)
{
	return this->convertionMap->at(position);
}
