/*
 *  TMtrie.h
 *  TextMiningCompiler
 *
 *  Created by pierre on 11/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef TMTRIE_H_
# define TMTRIE_H_

# include "TMalphabetMap.h"

# define SIZE_ALPHABET 127          /* Using a-z and space */
# define MAXDEPTH 42                /* Supporting 20 character depth of dictionary */
# define MB_512 536870912			/*	536 870 912 */
# define MB_256 268435456
# define MB_128 134217728
# define MB_64 67108864
# define MB_32 32554432
# define MB_16 16777216


/*
** Our Trie Structure in Memory:
** Header at the begining of our structure:
**  [alphabet size][TrieSize (unsigned long int) ][127 char long array containing the mapping of our alphabet][our alphabet]
** Cell Reprensatation after the header
**  [(int= 4 octet) Frequence][special pointer array:  alphabet size * sizeof(int)]
**  The frequence will be set to 0 if it's not a word so by default the tree root will have 0 (all the time)
**  Each cell of the special pointer array will be set to 0 if pointer NULL.. else it will point to a Cell number id.
*/



/* Trie represented as class */
class Trie {
	private:
		char*		trie;
	private:
	/* we allocate as much as we can, because we don't know yet, how much we will need */
		void		initTrieMemory(unsigned long int sizeNeeded); 
	/* We need to put some information about the structure at the begining of our Trie */
		void		initTrieHeaderWithAlphabet(AlphabetMap alphaMap);
	/* Once we've put every word we needed in our Trie, we can reduce it, so it'll take less memory */
		void		resizeTrieMemory(void);
	/* add a word to the trie with the frequence */
		void		addWord(std::string word, unsigned long int frequence);
	/* construct the Trie */
		void		parseFileToTrie(std::string filePath);
	public:
		Trie(unsigned long int sizeNeeded, AlphabetMap alphaMap, std::string filePath);
		~Trie();
	public:
		int			getFrequence(std::string word);
		int			getFrequence(char		*word);
		/* Dump the structure char* trie to the file */
		int			compileTrie(std::string destinationPath);
	
};
#endif /* !TMTRIE_H_ */