/*
 *  serializer.h
 *  TextMiningCompiler
 *
 *  Created by Alex on 23/11/10.
 *  Copyright 2010 Epita. All rights reserved.
 *
 */
#ifndef __SERIALIZER__
# define __SERIALIZER__
# include <iostream>
# include "TMTrieDynamic.h"

class Serializer
{
private:
	TrieDynamic	*abr;
	std::string		fileOut;
	std::string		fileIn;

public:
	Serializer(TrieDynamic *abr);
	~Serializer();
	
	void			writeInFile(std::string fileOut);
	TrieDynamic*	readFromFile(std::string fileIn);
	void			setFileOut(std::string fileOut);
	void			setFileIn(std::string fileIn);
	void			setAbr(TrieDynamic *abr);
	std::string		getFileOut();
	std::string		getFileIn();
	TrieDynamic*	getAbr();
};
#endif