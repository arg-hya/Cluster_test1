#include "stdafx.h"
#include "IRISInterface.h"

IRISInterface::IRISInterface()
{
	TOT_SAMPLES = 150;
	TOT_DIM = 4;	
	TOT_ATTRIBUTES = TOT_DIM + 1;
}

//IRISInterface::~IRISInterface()
//{
//	
//}

int IRISInterface::getTotSampleno()
{
	return TOT_SAMPLES;
}

int IRISInterface::getTotDimno()
{
	return TOT_DIM;
}

int IRISInterface::readFiletoString()
{
	unsigned int file_size;
	
	file.open("Datasets\\Iris.data", std::ios::in);

	if (!file.is_open())
	{
		// check for successful opening
		std::cout << "Input file could not be opened! Terminating!" << std::endl;
		exit(1);
	}

	file.seekg(0, std::ios::end);
	file_size = (unsigned int)file.tellg();
	file.seekg(0, std::ios::beg);
	str = new char[file_size + 1];
	file.read(str, file_size);
	str[file_size] = 0;

	file.close();

	return SUCCESS;
}

int IRISInterface::parseString()
{
	int k = 0, dim_indx = 0;
	float temp;
	int flag = 1;
	
	for (str = std::strtok(str, tokens); str; str = std::strtok(NULL, tokens))
	{
		if (1 == flag)
		{
			nodes[k].no = k + 1;
			nodes[k].dim = new int[TOT_DIM];
		}

		if (TOT_ATTRIBUTES != flag)
		{
			temp = (float)std::atof(str);
			nodes[k].dim[dim_indx] = (int)(temp * 10);
			dim_indx++;
		}
		else
		{
			flag = 0;
			dim_indx = 0;
			k++;
		}
		flag ++;
	}

	return SUCCESS;
}

node* IRISInterface::getPoints()
{
	nodes = new node[TOT_SAMPLES];
	readFiletoString();
	parseString();
	return nodes;
}

int IRISInterface::releasePoints()
{
	/*for (int i = 0; i < TOT_SAMPLES; i++)
	{
		if (nodes[i].dim)
		{
			delete[] nodes[i].dim;
			nodes[i].dim = NULL;
		}

		if (nodes[i].clusterNos.size() > 0)
		{
			std::vector<int>().swap(nodes[i].clusterNos);
		}

	}*/

	/*if (nodes)
	{
		delete nodes;
		nodes = NULL;
	}*/

	if (str)
	{
		delete[] str;
		str = NULL;
	}

	return SUCCESS;
}

int IRISInterface::showPoints()
{
	for (int i = 0; i < TOT_SAMPLES; i++)
	{
		std::cout << std::endl;

		for (int j = 0; j < TOT_DIM; j++)
		{
			std::cout << nodes[i].dim[j] << " ";
		}
	}
	return SUCCESS;
}