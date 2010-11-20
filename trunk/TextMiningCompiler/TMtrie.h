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

# define SIZE_ALPHABET 127          /* Using a-z and space */
# define MAXDEPTH 42                 /* Supporting 20 character depth of dictionary */


/* Trie represented as class */
class Trie {
private:
public:
	Trie();                          
	~Trie();                           
};
#endif /* !TMTRIE_H_ */