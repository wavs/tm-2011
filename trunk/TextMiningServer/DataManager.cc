/**
 ** \file DataManager.cc
 ** \author Thomas Ait-taleb
 ** \version 0.1
 ** \date 17 novembre 2010
 ** \brief Implémentation de la classe DataManager
 **/

#include "DataManager.hh"

DataManager::DataManager ()
{}

DataManager::~DataManager ()
{}

void
DataManager::loadFile(string filename)
{
	// FIXME
}

void
DataManager::dump()
{
	// FIXME
}

TResultsDictionnary
*DataManager::browseDataWithOptions(string word, int dist)
{
	// FIXME
}

string	jsonedResult(s_result	*res)
{
	stringstream s;	//create a stringstream

	s << "{\"word\":\"" << *res->word << "\",\"freq\":" 
					<< res->freq << ",\"distance\":" 
								 << res->dist << "}";
	
	return s.str();
}

string
DataManager::exportJSON(vector<s_result*> *results)
{
	stringstream s;
	
	s << "[";
	
	int i;
	for(i = 0; i < (results->size() - 1); i++)
		s << jsonedResult(results->at(i)) << ",";
	
	s << jsonedResult(results->at(i)) << "]";
	
	return s.str();
}

#define RESULT_TEST "[{\"word\":\"alzheimer\",\"freq\":1156353,\"distance\":1},\
{\"word\":\"alsheimer\",\"freq\":1212,\"distance\":1},\
{\"word\":\"altzheimer\",\"freq\":535,\"distance\":2}]"

void
DataManager::TEST_exportJSON()
{
	// Création du 1er résultat
	s_result	*res1	= (s_result*)calloc(0, sizeof(s_result));
	res1->word			= new string("alzheimer");
	res1->freq			= 1156353;
	res1->dist			= 1;
	
	// Création du 2eme résultat
	s_result	*res2	= (s_result*)calloc(0, sizeof(s_result));
	res2->word			= new string("alsheimer");
	res2->freq			= 1212;
	res2->dist			= 1;
	
	// Création du 3eme résultat
	s_result	*res3	= (s_result*)calloc(0, sizeof(s_result));
	res3->word			= new string("altzheimer");
	res3->freq			= 535;
	res3->dist			= 2;
	
	// Création du tableau de résultat
	vector<s_result*>		*results = new vector<s_result*>();
	results->push_back(res1);
	results->push_back(res2);
	results->push_back(res3);
	
	string res = exportJSON(results);
	
	if (res == RESULT_TEST)
		std::cout << "TEST JSON EXPORT SUCCESS." << std::endl;
	else
		std::cout << "TEST JSON EXPORT FAILED." << std::endl;

	
	delete res1;
	delete res2;
	delete res3;
	delete results;
}

