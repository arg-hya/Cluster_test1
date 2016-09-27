#pragma once
#include <iostream>
#include <fstream>

#include "Header.h"
class IRISInterface  
{
private:
	int TOT_SAMPLES = -1, TOT_DIM = -1, TOT_ATTRIBUTES = 1;
	std::ifstream file;
	char *str = NULL;
	const char* tokens = ",\n";

	node *nodes = NULL;

public :
	IRISInterface();
	//~IRISInterface();

	int getTotSampleno();
	int getTotDimno();
	node* getPoints();
	int releasePoints();

	int readFiletoString();
	int parseString();
	int showPoints();
};