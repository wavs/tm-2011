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

# define MB_1024 1073741824
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


typedef struct s_header{
	char				alphabetSize;
	uint32_t			trieSize;
	char				mapping[SIZE_ALPHABET];
	char				alphabet[SIZE_ALPHABET];	
} s_header;

/* Trie represented as class */
class Trie {
	private:
		void*		trieMemoryChunk;
		uint32_t*	trieRoot;
		s_header*	header;
		uint32_t	maxSizeTrie;
		uint32_t	cellSize;
	/* we allocate as much as we can, because we don't know yet, how much we will need */
		void		initTrieMemory(uint32_t sizeNeeded); 
	/* We need to put some information about the structure at the begining of our Trie */
		void		initTrieHeaderWithAlphabet(AlphabetMap &alphaMap);
	/* Once we've put every word we needed in our Trie, we can reduce it, so it'll take less memory */
		void		resizeTrieMemory(void);
	/* add a word to the trie with the frequence */
		void		addWord(std::string word, uint32_t frequence);
	/* construct the Trie */
		void		parseFileToTrie(std::string filePath);
	private:
		void	setHeaderMapping(std::vector<char> *_mapping);
		void	setHeaderAlphabet(std::set<char> &_alphabet);
		void	setHeaderTrieSize(unsigned long int _trieSize);
	private:
	 /* return the new cell and increment the size of the trie in the header*/
		uint32_t	getSpecialPosition(uint32_t *currentCell, char letter);
		void		setSpecialPosition(uint32_t *currentCell, char letter, uint32_t position);
		uint32_t	*addCell(uint32_t	*currentCell, char	letter, uint32_t frequence);
		uint32_t	*getCell(uint32_t	*currentCell, char letter);
		void	setFrequence(uint32_t	*currentCell, uint32_t frequence);
	public:
		Trie(unsigned long int sizeNeeded, AlphabetMap &alphaMap, std::string &filePath);
		~Trie();

		uint32_t			getFrequence(std::string word);
		/* Dump the structure char* trie to the file */
		int			compileTrie(std::string destinationPath);
	
};
#endif /* !TMTRIE_H_ */