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
# define MAXDEPTH 42                 /* Supporting 20 character depth of dictionary */


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
	/* We need to put some information about the structure at the begining of our Trie */
		void		initTrieWithAlphabet(AlphabetMap alphaMap);
	/* we allocate as much as we can, because we don't know yet, how much we will need */
		void		initTrieMemory(unsigned long int sizeNeeded); 
	/* Once we've put every word we needed in our Trie, we can reduce it, so it'll take less memory */
		void		resizeTrieMemory(void);
	
		void		addWord(std::string word, );
	public:
		Trie(unsigned long int sizeNeeded, AlphabetMap alphaMap);
		~Trie();
	public:
		int			getFrequence(std::string word);
		int			getFrequence(char		*word);
	
};
#endif /* !TMTRIE_H_ */