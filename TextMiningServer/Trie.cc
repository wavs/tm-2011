/**
 ** \file Trie.cc
 ** \author Pierre Guilbert
 ** \version 0.1
 ** \date 23 novembre 2010
 ** \brief Implémentation de la classe Trie
 **/

#include "Trie.hh"

using namespace std;

Trie::Trie(std::string &filePath):
trieRoot(NULL)
{
	//this->parseFileToTrie(filePath);
	
	ifstream		ifs (filePath.c_str(), ifstream::in);
	queue<string>	queue_1;
	queue<s_node*>	queue_2;
	
	if (ifs.is_open())
	{
		string lineRead;
		
		// Lecture ligne par ligne
		while (std::getline(ifs, lineRead))
		{
			// Cas d'une ligne avec un noeud
			if (lineRead.compare("-") != 0)
			{
				// Stockage dans la première pile
				queue_1.push(lineRead);
			}
			// Cas d'une ligne séparatrice
			else
			{
				s_node	*father = NULL;
				
				while (!queue_1.empty())
				{
					// Traitement des derniers noeuds empilés
					//string	currentElt = stack_1.top();
					//stack_1.pop();
					string	currentElt = queue_1.front();
					queue_1.pop();
					
					// Récupération des données de la chaine
					char		letter;
					uint32_t	frequence;
					char		sonOrBrother;
					char		nodeOrLeaf;
					sscanf(currentElt.c_str(), "%c %d %c %c", &letter, &frequence, &sonOrBrother, &nodeOrLeaf);
					
					// Création du noeud
					s_node	*currentNode = (s_node*)calloc(1, sizeof(s_node));
					currentNode->sons = NULL;
					currentNode->brother = NULL;
					currentNode->letter = letter;
					currentNode->frequence = frequence;
					
					// Cas de la racine de l'arbre
					if (sonOrBrother == 'r')
						trieRoot = currentNode;
					else
					{
						// Récupération du noeud père // FIXME ou father != NULL
						if (!queue_2.empty())
						{
							if (father == NULL)
							{
								father = queue_2.front();
								queue_2.pop();
							}
							
							// Cas d'un frère
							if (sonOrBrother == 'b')
								father->brother = currentNode;
							
							// Cas d'un fils
							if (sonOrBrother == 's')
								father->sons = currentNode;
						}
					}
					
					// Stockage dans la deuxième pile du noeud
					// sauf pour les feuilles
					if (nodeOrLeaf == 'n')
						queue_2.push(currentNode);
				}
			}
		}
		
		// Fermeture du file descriptor
		ifs.close();
	}
	else
		std::cout << "Error: Impossible d'ouvrir le fichier de données." << std::endl;
	
}

Trie::~Trie(){
	this->deleteNode(this->trieRoot);
}


void		Trie::parseFileToTrie(std::string filePath){
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
				
				this->trieRoot = this->addWord(this->trieRoot, tokens[0], frequenceWordInt);
#if DEBUG
				std::cout << tokens[0] << "/" << frequenceWordInt << std::endl;
#endif /* DEBUG */
			}
		}
		myFileStream.close();
	}
	else
	{
		std::cerr << "Unable to open file"; 
	}
	
}

s_node		*Trie::addWord(s_node  *currentNode, std::string word, uint32_t frequence)
{
	s_node *brothers;
	if (word.size() != 0) {
		/* brother -< currentMode */
		brothers = currentNode;
		currentNode = this->getCell(currentNode, word[0]);
		if (currentNode != NULL) {
			if (word.size() == 1) {
				this->setFrequence(currentNode, frequence);
			}
			else {
				currentNode->sons = this->addWord(currentNode->sons, word.substr(1), frequence);
			}
			//currentNode->sons = this->addWord(currentNode, word.substr(1), frequence);
			return brothers;
			
		}
		else{
			if (word.size() == 1) {
				if (brothers) {
					currentNode = this->addCell(brothers, word[0], frequence);
					
				}
				else {
					currentNode = this->addCell(NULL, word[0], frequence);
					brothers = currentNode;
				}
				
			}
			else {
				if (brothers) {
					currentNode = this->addCell(brothers, word[0], 0);
					
				}
				else {
					currentNode = this->addCell(NULL, word[0], 0);
					brothers = currentNode;
				}
				currentNode->sons = this->addWord(currentNode->sons, word.substr(1), frequence);
				
			}
			
			return  brothers;
		}
		
	}
	else {
		return (NULL);
	}
	
	
#if 0
	
	s_node	*currentCell = this->trieRoot;
	s_node	*tempCell = NULL;
	s_node	*nextCell = this->trieRoot;
	
	int			i;
	
	for (i = 0; i < word.size() - 1; ++i) {
		tempCell = this->getCell(nextCell, word[i]);
		if (currentCell != NULL) {
			nextCell = currentCell->sons;
		}
		else {
			currentCell = this->addCell(nextCell, word[i], 0);
			if ((this->trieRoot == NULL) && (i == 0) ){
				this->trieRoot = currentCell;
			}
			if (!currentCell) return;
			nextCell = currentCell;
		}
	}
	
	currentCell = this->getCell(nextCell, word[i]);
	if (currentCell != NULL) {
		this->setFrequence(currentCell, frequence);
		nextCell = currentCell->sons;
	}
	else {
		currentCell = this->addCell(nextCell, word[i], frequence);
		if (!currentCell) return;
		nextCell = NULL;
	}
#endif / *old addWord* /
}

s_node	*Trie::addCell(s_node	*currentCell, char	letter, uint32_t frequence){
	
	s_node *newCell = new s_node;
	
	while ((currentCell != NULL) && (currentCell->brother != NULL)) {
		currentCell = currentCell->brother;
	}
	
	
	if (newCell) {
		newCell->brother	= NULL;
		newCell->sons		= NULL;
		newCell->frequence	= frequence;
		newCell->letter		= letter;
		if (currentCell) {
			currentCell->brother = newCell;
		}
	}	
	
	return newCell;
	
}

/* return the node of the letter */
s_node	*Trie::getCell(s_node	*currentCell, char letter){
	
	while ((currentCell != NULL) && (currentCell->letter != letter)) {
		currentCell = currentCell->brother;
	}	
	return currentCell;
}



void	Trie::setFrequence(s_node	*currentCell, uint32_t frequence){
	currentCell->frequence = frequence;
}

uint32_t	Trie::getFrequence(std::string word){
	s_node	*currentCell = NULL;
	s_node	*nextCell = this->trieRoot;
	
	int			i;
	
	for (i = 0; i < word.size(); ++i) {
		currentCell = this->getCell(nextCell, word[i]);
		if (currentCell != NULL) {
			nextCell = currentCell->sons;
		}
		else {
			nextCell = NULL;
		}
		
	}
	
	return currentCell->frequence;
}

void		Trie::deleteNode(s_node	*node)
{ 
	if (node != NULL) {
		deleteNode(node->brother);
		deleteNode(node->sons);
		delete node;
	}	
	return;	
}


int			Trie::compileTrie(std::string destinationPath){
	/* FIXME */
	return 0;
}


s_node*
Trie::getBrothers()
{
	return this->trieRoot->brother;
}

s_node*
Trie::getSons()
{
	return this->trieRoot->sons;
}

char
Trie::getLetter()
{
	return this->trieRoot->letter;
}

uint32_t
Trie::getNodeFrequence()
{
	return this->trieRoot->frequence;
}

s_node*
Trie::getTrieRoot()
{
	return this->trieRoot;
}

void
Trie::setTrieRoot(s_node* trieRoot)
{
	this->trieRoot = trieRoot;
}

void
Trie::printTrie(s_node* node, int space)
{
	if (node != NULL)
	{
		for (int i = 0; i < space; i++)
			std::cout << " ";
		std::cout << node->letter << " " << node->frequence << " floor : " << space << std::endl;
		this->printTrie(node->brother, space+1);
		this->printTrie(node->sons, space+1);
	}
}

