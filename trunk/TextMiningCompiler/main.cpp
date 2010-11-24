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


#include "src/TMalphabetMap.h"
#include "src/TMtrie.h"
#include "src/TMTrieDynamic.h"
#include "src/serializer.h"

#define DEFAULTPATH "/Users/gui/Documents/lectures EPITA/ING3/TextMining/textmining/Projet/tm.out"

#define PATH "/Users/gui/Documents/lectures EPITA/ING3/TextMining/textmining/Projet/test.txt"

void testMap(void)
{
	std::map<char,int> mymap;
	std::map<char,int>::iterator it;
	
	mymap['a']=50;
	mymap['b']=100;
	mymap['c']=150;
	mymap['d']=200;
	mymap['b']=14;
		
	// print content:
	std::cout << "elements in mymap:" << std::endl;
	for (it = mymap.begin(); it != mymap.end(); it++) {
		std::cout << it->first << "=>" << it->second << std::endl;
	}
}

void testSet(void)
{
	std::set<char> myset;
	std::set<char>::iterator it;
	
	std::vector<char> convertionMap (127);
	
	for (int i = 0; i < 128; ++i) {
		convertionMap[i] = i;
	}
	convertionMap['f'] = 13;
	convertionMap['d'] = 12;
	std::cout << convertionMap[127] << std::endl;
}


/*
** unit test 
** for each word in the file, we check the tree and compare the frequence
** we should have with the frequence we get
*/
void	testTrie(std::string &filePath, TrieDynamic *mytrie)
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
				
				/* here we test with the trie */
				if (mytrie->getFrequence(tokens[0]) != frequenceWordInt) {
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
		myFileStream.close();
	}
	else
	{
		std::cerr << "Unable to open file"; 
	}
}
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

void	testAlphaMapAndOldTrie(std::string filePath)
{
	AlphabetMap *alphaMap = new AlphabetMap(filePath);
	alphaMap->printAlphabet();
	alphaMap->printSizeOfProperties();
	alphaMap->printConvertionMap();
	std::cout << "position of a:"<<(int)alphaMap->getPosition('a') << std::endl;
	
	Trie *mytrie = new Trie(MB_512, *alphaMap, filePath);
	
	delete	 mytrie;

	
}

void testOpenFile(std::string &filePath, std::string &destinationPath)
{
	TrieDynamic *mytrie = new TrieDynamic(filePath);
	std::cout << "we succeed in creating the trie" << std::endl;

	mytrie->compileTrieToFile(destinationPath);
	std::cout << "we Succeed in compiling the tree" << std::endl;

	//testTrie(filePath, mytrie);
	
	//mytrie->printTrie(mytrie->getTrieRoot(), 0);
	//mytrie->testMemoryTree();
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
		testOpenFile(*filePath, *destinationPath);
		// compile tree from class
		// save to destinationPath
		std::cout << *filePath << " " << *destinationPath << " "<< std::endl;

	}
	else {
		std::cerr << "Not enough argument, didn't compute" << std::endl;
		return 1;
	}
	
    return 0;
}
