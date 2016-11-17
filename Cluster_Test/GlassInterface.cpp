#include "stdafx.h"
#include "GlassInterface.h"

GlassInterface::GlassInterface()
{
	TOT_SAMPLES = 214;
	TOT_DIM = 9;	
	TOT_ATTRIBUTES = TOT_DIM + 2;
}

//GlassInterface ::~GlassInterface ()
//{
//	
//}

int GlassInterface::getTotSampleno()
{
	return TOT_SAMPLES;
}

int GlassInterface::getTotDimno()
{
	return TOT_DIM;
}

int GlassInterface::readFiletoString()
{
	unsigned int file_size;
	
	file.open("Datasets\\Glass_DataSet.data", std::ios::in);

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

int GlassInterface::parseString()
{
	int k = 0, dim_indx = 0;
	double temp;
	int flag = 1;
	
	for (str = std::strtok(str, tokens); str; str = std::strtok(NULL, tokens))
	{
		if (1 == flag)
		{
			nodes[k].no = k + 1;
			nodes[k].dim = new double[TOT_DIM];
		}

		else if (TOT_ATTRIBUTES != flag)
		{
			temp = (double)std::atof(str);
			//nodes[k].dim[dim_indx] = (int)(temp * 10);
			nodes[k].dim[dim_indx] = temp;
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

node* GlassInterface::getPoints()
{
	nodes = new node[TOT_SAMPLES];
	readFiletoString();
	parseString();
	return nodes;
}

int GlassInterface::releasePoints()
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

int GlassInterface::showPoints()
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