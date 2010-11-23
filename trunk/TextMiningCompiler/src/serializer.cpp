/*
 *  serializer.cpp
 *  TextMiningCompiler
 *
 *  Created by Alex on 23/11/10.
 *  Copyright 2010 Epita. All rights reserved.
 *
 */

#include <iostream>
#include <stack>
#include <fstream>
#include "serializer.h"
#include "TMTrieDynamic.h"

Serializer::Serializer(TrieDynamic *abr)
{
	this->abr = abr;
}

Serializer::~Serializer()
{
}

void
Serializer::writeInFile(std::string fileOut)
{
	std::stack<s_node*> nodeStack;
	this->fileOut = fileOut;
	bool flag = true;
	s_node* currentNode = this->abr->getTrieRoot();
	std::ofstream f ((this->fileOut).c_str(), std::ios::out | std::ios::trunc);
	if (f)
	{
		f << currentNode->letter << " " <<	currentNode->frequence << " r";
		if (currentNode->sons == NULL && currentNode->brother == NULL)
			f << " f"<< std::endl;
		else 
			f << " n" << std::endl;
		f << "-" << std::endl;

		nodeStack.push(currentNode);
		
		while (!nodeStack.empty())
		{
			currentNode = nodeStack.top();
			nodeStack.pop();
			flag = false;
			if (currentNode->brother != NULL)
			{
				flag = true;
				f << currentNode->brother->letter << " " <<	currentNode->brother->frequence << " b";
				if (currentNode->brother->sons == NULL && currentNode->brother->brother == NULL)
					f << " f"<< std::endl;
				else 
					f << " n" << std::endl;
				nodeStack.push(currentNode->brother);
			}
			if(currentNode->sons != NULL)
			{
				flag = true;
				f << currentNode->sons->letter << " " <<	currentNode->sons->frequence << " s";
				if (currentNode->sons->sons == NULL && currentNode->sons->brother == NULL)
					f << " f"<< std::endl;
				else 
					f << " n" << std::endl;
				nodeStack.push(currentNode->sons);
			}
			if (flag)
				f << "-" << std::endl;
		}
		
		f.close();
	}
	else {
		std::cerr << "Erreur à l'ouverture !" << std::endl;
	}
}

TrieDynamic*
Serializer::readFromFile(std::string fileIn)
{
	this->fileIn = fileIn;
	std::ifstream fichier((this->fileIn).c_str(), std::ios::in);  // on ouvre le fichier en lecture
	
	if(fichier)  // si l'ouverture a réussi
	{       
		// instructions
		fichier.close();  // on ferme le fichier
	}
	else  // sinon
		std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
	return NULL;
}


void
Serializer::setFileOut(std::string fileOut)
{
	this->fileOut = fileOut;
}

void
Serializer::setFileIn(std::string fileIn)
{
	this->fileIn = fileIn;
}

void
Serializer::setAbr(TrieDynamic *abr)
{
	this->abr = abr;
}

std::string
Serializer::getFileOut()
{
	return this->fileOut;
}

std::string
Serializer::getFileIn()
{
	return this->fileIn;
}

TrieDynamic*
Serializer::getAbr()
{
	return this->abr;
}



