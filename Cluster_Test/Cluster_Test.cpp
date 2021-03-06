// Cluster_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "IRISInterface.h"
#include "GlassInterface.h"
#include "ClusterAlgo.h"
#include <vector>
#include "Header.h"

//struct node {
//	int no = -1;	
//	std::vector<int> clusterNos;	
//	int numberOfAssignedClusters = 0;
//	int *dim = NULL;
//};

int _tmain(int argc, _TCHAR* argv[])
{
	
	int totSample = -1, totDim = -1 ;

	//IRISInterface *intr = new IRISInterface();
	GlassInterface *intr = new GlassInterface();
	totSample = intr->getTotSampleno();
	totDim = intr->getTotDimno();

	ClusterAlgo *cls = new ClusterAlgo(intr->getTotSampleno(), intr->getTotDimno());
	

	/*intr->readFiletoString();
	intr->parseString();*/
	//intr->showPoints();
	cls->allocatePoints(intr->getPoints());
	cls->run(); 
	//cls->showResultsALL();
	cls->showResults();
	//cls->printPointsWithClusters();

	cls->compressClusters();

	cls->compressClusters();
	cls->compressClusters();
	cls->compressClusters();

	cls->showResults();

//	intr->showPoints();

	intr->releasePoints();
	delete cls;	// cls->~ClusterAlgo();

	delete intr;

	cin.get();

	return 0;
}

