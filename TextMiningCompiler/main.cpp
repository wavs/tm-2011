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

#include "TMalphabetMap.h"

#define DEFAULTPATH "tm.out"


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

void testOpenFile(std::string &filePath)
{
	AlphabetMap alphaMap(filePath);
	alphaMap.printAlphabet();
	alphaMap.printSizeOfProperties();
	alphaMap.printConvertionMap();
	std::cout << "position of a:"<<(int)alphaMap.getPosition('a') << std::endl;
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
		testOpenFile(*filePath);
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
