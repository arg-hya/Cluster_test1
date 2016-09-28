#pragma once
//#include "stdafx.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <random>
#include "Header.h"
#include "FFT_WIKI.h"

class ClusterAlgo
{
private:

	//struct node {
	//	int no = -1;
	//	//std::vector<int> clusterNos;
	//	std::vector<int> clusterNos;
	//	//int *clusterNos = NULL;
	//	int numberOfAssignedClusters = 0;
	//	int *dim = NULL;
	//};

	struct FFTPoints {
		double *samples = NULL;
	};

	FFTPoints *fftOfPoints = NULL;
	//int pointsLeft;
	//bool *storePoint;

	int getFFTofAllPoints();

	int getRandomPoints(int no_testPoints, int * testPoints);
	//bool isEvaluated(int pos);
	int hard_clustering(int totDim, int *Input, int init_no_points, int *Output, int& out_init_no_points);
	int getSimilarPoints(int &no_testPoints, int * testPoints);

	bool isAllMarkedAtleastOnce();

	//int markPointsIntra(int &init_no_points, node* &testDeck, int clusternumber);
	int formCluster(int &no_testPoints, int * testPoints, double *newCluster);
	int calculateThreshold(int &no_testPoints, int * testPoints, double&  threshold);
	int markPoints(int clusterNos, double *newCluster, double threshold); 

	std::vector<double*> Clusters;	//Stores the best fittness level of each generation.

public:
	int totSample = -1, totDim = -1;
	node *Nodes;

	ClusterAlgo(int _totSample = -1, int _totDim = -1);
	~ClusterAlgo();

	int allocatePoints(node *Points);

	int run();

	int printPointsWithClusters();

};
