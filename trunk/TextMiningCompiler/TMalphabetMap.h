/*
 *  TMalphabetMap.h
 *  TextMiningCompiler
 *
 *  Created by pierre on 11/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef TMALPHABETMAP_H_
# define TMALPHABETMAP_H_

# include <string>
# include <set>
# include <vector>

# define ALPHABET_SIZE_MAX 127 /* ASCII */

class AlphabetMap {
private:
	std::vector<char> *convertionMap;
	std::set<char> alphabet;
	
	/* construct the convertionMap */
	void parseFileToAlphabet(std::string path);
	void addingWordCharToAlphabet(std::string word);
	void convertAlphabetToConvertionMap(void);
	/* initialiseur */
	void initConvertionMap(void);
public:
	AlphabetMap(std::string path);                            /* */
	~AlphabetMap();                           /* Freeing Memory*/
	
	void printSizeOfProperties(void); /* For Debug purpose */
	void printAlphabet(void);
	void printConvertionMap(void);
	char getPosition(char position);
};
#endif /* !TMALPHABETMAP_H_*/