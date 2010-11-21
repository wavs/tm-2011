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


#include "TMalphabetMap.h"
#include "TMtrie.h"

#define DEFAULTPATH "tm.out"

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


void testOpenFile(std::string &filePath, std::string &destinationPath)
{
	AlphabetMap *alphaMap = new AlphabetMap(filePath);
	//alphaMap->printAlphabet();
	//alphaMap->printSizeOfProperties();
	//alphaMap->printConvertionMap();
	//std::cout << "position of a:"<<(int)alphaMap.getPosition('a') << std::endl;
	
	Trie *mytrie = new Trie(MB_512, *alphaMap, filePath);
	std::cout << "we succeed in creating the trie" << std::endl;
#if 1
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
#endif
	mytrie->compileTrie(destinationPath);

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
