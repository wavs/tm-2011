#include <iostream>
#include <string>
#include <sys/types.h>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <new>


#include "src/TMTrieDynamic.h"
#include "src/serializer.h"

#define DEFAULTPATH "tm.out"

/*!
** \brief unit test 
** for each word in the file, we check the tree and compare the frequence
** we should have with the frequence we get
*/
void	testTrie(std::string &filePath, TrieDynamic *mytrie)
{
	std::fstream		myFileStream;
	std::string			myLine;
	std::istringstream	frequenceWordStr;
	unsigned long int	frequenceWordInt;
	unsigned long int	countError = 0;
	unsigned long int	nombreDeMots = 0;
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
				nombreDeMots += 1;
				/* here we test with the trie */
				if (mytrie->getFrequence(tokens[0]) != frequenceWordInt) {
					countError += 1;
					std::cout << "NOT OK: tokens0: " << tokens[0] << "/frequence from trie: " << mytrie->getFrequence(tokens[0])
					<< "/realfrequence: " << frequenceWordInt << std::endl;
				}
#if 0
				else {
					
					std::cout << "OK    : tokens0: " << tokens[0] << "/frequence from trie: " << mytrie->getFrequence(tokens[0])
					<< "/realfrequence: " << frequenceWordInt << std::endl;	
				}
#endif /* 0 */

			}
		}
		std::cout << countError <<" Errors on: " << nombreDeMots << " words tested."<< std::endl;
		myFileStream.close();
	}
	else
	{
		std::cerr << "Unable to open file"; 
	}
}

/*!
 * \brief unit test
 *  We check the frequence in the trie of some words predetermined
 */
void testSomeWord(TrieDynamic *mytrie)
{
	std::string test1("n942a");
	std::cout << "my frequence n942a: " << mytrie->getFrequence(test1) << std::endl;
	
	std::string test2("n942");
	std::cout << "my frequence n942: " << mytrie->getFrequence(test2) << std::endl;
	
	std::string test3("n936");
	std::cout << "my frequence n936: " << mytrie->getFrequence(test3) << std::endl;
	
	std::string test4("n941");
	std::cout << "my frequence n941: " << mytrie->getFrequence(test4) << std::endl;
	
	std::string test5("n939");
	std::cout << "my frequence n939: " << mytrie->getFrequence(test5) << std::endl;
}



/*!
 * \brief  creating the trie from the compiled file
 */

TrieDynamic *testDecompileTrieFromFile(std::string &filePath)
{
	TrieDynamic *mytrie = new TrieDynamic();
	mytrie->importCompiledTrie(filePath);
	return mytrie;
}


/*!
 * \brief unit test
 ** testing compilation of the Trie and decompilation
 */
void testOpenFile(std::string &filePath, std::string &destinationPath)
{
	TrieDynamic *mytrie;
#if 1
	mytrie = new TrieDynamic(filePath);
	std::cout << "we succeed in creating the trie" << std::endl;

	mytrie->compileTrieToFile(destinationPath);
	std::cout << "we Succeed in compiling the tree" << std::endl;

	//testTrie(filePath, mytrie);
	delete mytrie;
	/* testing the decompiler */
#endif
	mytrie = testDecompileTrieFromFile(destinationPath);
	std::cout << "we succeed in building the Trie from the compiled form"<< std::endl;
	std::cout << "we're now testing the compiled trie " << std::endl;
	testTrie(filePath, mytrie);
	
	
	//mytrie->printTrie(mytrie->getTrieRoot(), 0);
	//mytrie->testMemoryTree();
	std::cout << "freeing memory" << std::endl;
	delete mytrie;
}





int main (int argc, char * const argv[]) {

	std::string *filePath;
	std::string *destinationPath;
	
	
	if (argc > 1)
	{
		filePath = new std::string(argv[1]);
		
		if (argc > 2) {
			destinationPath = new std::string(argv[2]);
		}
		else {
			destinationPath = new std::string(DEFAULTPATH);
		}
		// build tree from file
		//testOpenFile(*filePath, *destinationPath);
		TrieDynamic *mytrie = new TrieDynamic(*filePath);
		// compile tree from class
		Serializer serial(mytrie);
		serial.writeInFile(*destinationPath);
		// save to destinationPath
		delete mytrie;
		//std::cout << *filePath << " " << *destinationPath << " "<< std::endl;

	}
	else {
		std::cerr << "Not enough argument, didn't compute" << std::endl;
		return 1;
	}
	
    return 0;
}
