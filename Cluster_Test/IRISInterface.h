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

	int readFiletoString();
	int parseString();

public :
	IRISInterface();
	//~IRISInterface();

	int getTotSampleno();
	int getTotDimno();
	node* getPoints();
	int releasePoints();

	int showPoints();
};