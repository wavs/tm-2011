/**
 ** \file DataManager.cc
 ** \author Thomas Ait-taleb
 ** \version 0.1
 ** \date 17 novembre 2010
 ** \brief Implémentation de la classe DataManager
 **/

#include "DataManager.hh"

#define RESULT_TEST "[{\"word\":\"alzheimer\",\"freq\":1156353,\"distance\":1},\
{\"word\":\"alsheimer\",\"freq\":1212,\"distance\":1},\
{\"word\":\"altzheimer\",\"freq\":535,\"distance\":2}]"

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

TResults
*DataManager::browseDataWithOptions(string word, int dist)
{
	// FIXME
	
	////////////////////////////
	// FOR TEST PURPOSES ONLY //
	////////////////////////////
	TResults	*test = new TResults();
	
	s_result	*res1	= (s_result*)calloc(0, sizeof(s_result));
	res1->word			= new string("alzheimer");
	res1->freq			= 1156353;
	res1->dist			= 1;
	test->push_back(res1);
	
	s_result	*res2	= (s_result*)calloc(0, sizeof(s_result));
	res2->word			= new string("alsheimer");
	res2->freq			= 525;
	res2->dist			= 1;
	test->push_back(res2);
	
	s_result	*res3	= (s_result*)calloc(0, sizeof(s_result));
	res3->word			= new string("altzheimer");
	res3->freq			= 535;
	res3->dist			= 0;
	test->push_back(res3);
	
	s_result	*res4	= (s_result*)calloc(0, sizeof(s_result));
	res4->word			= new string("bltzheimer");
	res4->freq			= 515;
	res4->dist			= 0;
	test->push_back(res4);
	
	s_result	*res5	= (s_result*)calloc(0, sizeof(s_result));
	res5->word			= new string("aluzheimer");
	res5->freq			= 525;
	res5->dist			= 1;
	test->push_back(res5);
	
	s_result	*res6	= (s_result*)calloc(0, sizeof(s_result));
	res6->word			= new string("aloheimer");
	res6->freq			= 535324;
	res6->dist			= 1;
	test->push_back(res6);
	
	s_result	*res7	= (s_result*)calloc(0, sizeof(s_result));
	res7->word			= new string("altzheimer");
	res7->freq			= 535;
	res7->dist			= 2;
	test->push_back(res7);
	
	s_result	*res8	= (s_result*)calloc(0, sizeof(s_result));
	res8->word			= new string("alvzheimer");
	res8->freq			= 525;
	res8->dist			= 1;
	test->push_back(res8);
	
	return test;
	////////////////////////////
	// FOR TEST PURPOSES ONLY //
	////////////////////////////
}

string	jsonedResult(s_result	*res)
{
	stringstream s;	//create a stringstream

	s << "{\"word\":\"" << *res->word << "\",\"freq\":" 
					<< res->freq << ",\"distance\":" 
								 << res->dist << "}";
	
	return s.str();
}

bool sortDistance(s_result *obj1, s_result *obj2)
{
	return (obj1->dist <= obj2->dist);
}

bool sortFrequence(s_result *obj1, s_result *obj2)
{
	if (obj1->dist <= obj2->dist)
		return (obj1->freq > obj2->freq);
	
	return false;
}

bool mycomp (char c1, char c2)
{ return tolower(c1)<tolower(c2); }

bool sortLexicographic(s_result *obj1, s_result *obj2)
{
	if (obj1->dist <= obj2->dist)
		if (obj1->freq >= obj2->freq)
			return std::lexicographical_compare(obj1->word->begin(), obj1->word->end(), obj2->word->begin(), obj2->word->end());
	
	return false;
}


TResults
*DataManager::refineResults(TResults *results)
{
	// Sorting distance
	sort (results->begin(), results->end(), sortDistance);
	
	// Sorting frequence
	sort (results->begin(), results->end(), sortFrequence);
	
	// Sorting lexicographicaly word
	sort (results->begin(), results->end(), sortLexicographic);
	
	return results;
}

string
DataManager::exportJSON(TResults *results)
{
	if (results != NULL) {
	
		stringstream s;
	
		s << "[";
	
		int i;
		for(i = 0; i < (results->size() - 1); i++)
			s << jsonedResult(results->at(i)) << ",";
	
		s << jsonedResult(results->at(i)) << "]";
		
		return s.str();
	}
	
	return NULL;
}

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

