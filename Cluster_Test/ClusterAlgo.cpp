// Cluster_Test1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "ClusterAlgo.h"


ClusterAlgo::ClusterAlgo(int _totSample, int _totDim )
{
	srand((unsigned int)time(NULL));	// initialize random seed	

	totSample = _totSample;
	totDim = _totDim;

	fftOfPoints = new FFTPoints[_totSample];
	for (int i = 0; i < _totSample; i++)
	{
		fftOfPoints[i].samples = new double[_totDim];
	}

//	pointsLeft = totSample;

	Nodes = NULL;

//	storePoint = new bool[totSample];
//	for (int i = 0; i < totSample; i++)	storePoint[i] = false;
	//node *Nodes = new node[totSample];

	//for (int i = 0; i < totSample; i++)
	//{
	//	Nodes[i].no = i;
	//	Nodes[i].dim = new double[totDim];
	//}
}


ClusterAlgo::~ClusterAlgo()
{
	/*if (storePoint)
	{
		delete[] storePoint;
		storePoint = NULL;
	}*/

	for (int i = 0; i < totSample; i++)
	{
		if (fftOfPoints[i].samples)
		{
			delete[] fftOfPoints[i].samples;
			fftOfPoints[i].samples = NULL;
		}		
	}

	if (fftOfPoints)
	{
		delete[] fftOfPoints;
		fftOfPoints = NULL;
	}

	if (Clusters.size() > 0)
	{
		std::vector<double*>().swap(Clusters);
	}
}

int ClusterAlgo::allocatePoints(node *Points)
{
	//Nodes = new node[totSample];
	Nodes = Points;
	return SUCCESS;
}

int ClusterAlgo::getFFTofAllPoints()
{
	for (int i = 0; i < totSample; i++)
	{
//		fft_test1(totDim, Nodes[i].dim, fftOfPoints[i].samples);
	}
	return SUCCESS;
}

//bool ClusterAlgo::isEvaluated(int pos)
//{
//	return storePoint[pos];
//}

int ClusterAlgo::getRandomPoints(int no_testPoints, int * testPoints)
{
	int k, i;
	//if (pointsLeft < no_testPoints)	no_testPoints = pointsLeft;

	k = 0;
	do
	{
		int temp = RANDOM(0, totSample);

	//	if (isEvaluated(temp))	continue;

		for (i = 0; i < k; i++)
		{
			if (testPoints[i] == temp)	break;
		}

		if (k == i)	testPoints[k++] = temp;

	} while (k < no_testPoints);

	return SUCCESS;
}

int ClusterAlgo::hard_clustering(int totDim, int *Input, int init_no_points, int *Output, int out_init_no_points)
{
	//
	unsigned int min_dis = 0;
	int a = -1, b = -1;

	for (int i = 0; i < init_no_points; i++)
	{
		for (int j = i; j < init_no_points; j++)
		{
			unsigned int dis = 0;

			for (int k = 0; k < totDim; k++)
			{
				dis += (unsigned int)std::pow(Nodes[Input[i]].dim[k] - Nodes[Input[j]].dim[k], 2);
			}

			dis = (unsigned int)std::sqrt(dis);

			if ((dis < min_dis) || (i == 0))
			{
				min_dis = dis;
				a = i;
				b = j;
			}
		}
	}
	//

	//
	unsigned int radius = min_dis;
	node CENTROID;
	for (int k = 0; k < totDim; k++)
	{
		CENTROID.dim[k] = Nodes[Input[a]].dim[k] + Nodes[Input[b]].dim[k];
		CENTROID.dim[k] /= 2;
	}
	//

	//
	bool *pos_array = new bool[init_no_points];
	for (int i = 0; i < init_no_points; i++)
	{
		pos_array[i] = false;
	}

	for (int j = 0; j < init_no_points; j++)
	{
		unsigned int dis = 0;

		for (int k = 0; k < totDim; k++)
		{
			dis += (unsigned int)std::pow(Nodes[Input[j]].dim[k] - CENTROID.dim[k], 2);
		}
		dis = (unsigned int)std::sqrt(dis);

		if (dis <= radius)
		{
			pos_array[j] = true;
		}
	}
	//

	//
	int noOfSimilarPoints = 0;
	int k = 0;
	for (int i = 0; i < init_no_points; i++)
	{
		if (pos_array[i] == true)	noOfSimilarPoints++;
	}

	Output = new int[noOfSimilarPoints + 1];

	for (int i = 0; i < noOfSimilarPoints; i++)
	{
		if (pos_array[i] == true)	Output[k++] = Input[i];
	}

	out_init_no_points = noOfSimilarPoints;
	//

	return SUCCESS;
}

int ClusterAlgo::getSimilarPoints(int &no_testPoints, int * testPoints)
{
	//Hard Selection Algo STARTS
	hard_clustering(totDim, testPoints, no_testPoints, testPoints, no_testPoints);
	//Hard Selection Algo ENDS

	/*int i = 0;
	while (i < no_testPoints)
	{
		storePoint[testPoints[i]] = true;		
		i++;
	}*/
	return SUCCESS;
}
bool ClusterAlgo::isAllMarkedAtleastOnce()
{
	for (int i = 0; i < totSample; i++)
	{
		if (Nodes[i].numberOfAssignedClusters > 0) continue;
		return false;
	}
	return true;
}
//int ClusterAlgo::markPointsIntra(int &init_no_points, node* &testDeck , int clusternumber)
//{
//	for (int i = 0; i < init_no_points; i++)
//	{
//		*(Nodes[testDeck[i].no].clusterNos + Nodes[testDeck[i].no].numberOfAssignedClusters) = clusternumber;
//		Nodes[testDeck[i].no].numberOfAssignedClusters++;
//	}
//
//	return SUCCESS;
//}
int ClusterAlgo::formCluster(int &no_testPoints, int * testPoints, double *newCluster)
{
	int *avg_dim = new int[no_testPoints];

	for (int i = 0; i < no_testPoints; i++)
	{
		double sum = 0.0;
		for (int j = 0; j < totDim; j++)
		{
			sum += Nodes[testPoints[i]].dim[j];
		}
		sum /= no_testPoints;
		avg_dim[i] = (int)sum;
	}

//	fft_test1(totDim, avg_dim, newCluster);

	return SUCCESS;
}

int ClusterAlgo::calculateThreshold(int &no_testPoints, int * testPoints, double threshold)
{
	double min_dis = 0.0;

	for (int i = 0; i < no_testPoints; i++)
	{
		for (int j = i; j < no_testPoints; j++)
		{
			unsigned int dis = 0;

			for (int k = 0; k < totDim; k++)
			{
				dis += (unsigned int)std::pow(fftOfPoints[testPoints[i]].samples[k] - fftOfPoints[testPoints[j]].samples[k], 2);
			}

			dis = (unsigned int)std::sqrt(dis);

			if ((dis < min_dis) || (i == 0))
			{
				min_dis = dis;
			}
		}
	}
	threshold = min_dis;

	return SUCCESS;
}
int ClusterAlgo::markPoints(int clusterNos, double *newCluster, double threshold)
{
	for (int i = 0; i < totSample; i++)
	{
		double score = 0.0;
		for (int j = 0; j < totDim; j++)
		{
			score = std::pow(fftOfPoints[i].samples[j] - newCluster[j], 2);
		}
		std::sqrt(score);

		if (score <= threshold)
		{
			Nodes[i].clusterNos.push_back(clusterNos);				// +Nodes[i].numberOfAssignedClusters;
			Nodes[i].numberOfAssignedClusters++;
		}
	}

	return SUCCESS;
}

int ClusterAlgo::printPointsWithClusters()
{
	for (int i = 0; i < totSample; i++)
	{
		std::cout << "Point No : " << Nodes[i].no << "     ";
		for (int j = 0; j < Nodes[i].numberOfAssignedClusters; j++)
		{
			std::cout << Nodes[i].clusterNos[j] << "   ";
		}
		std::cout << std::endl;
	}
	return SUCCESS;
}

int ClusterAlgo::run()
{
	getFFTofAllPoints();
	int clusternumber = 0;
	do
	{
		clusternumber++;

		int no_testPoints = 10;
		int *testPoints = new int[no_testPoints];
		for (int i = 0; i < no_testPoints; i++) testPoints[i] = -1;
		double *newCluster = new double[totDim];
		double threshold = 0.0;

		getRandomPoints(no_testPoints, testPoints);
		getSimilarPoints(no_testPoints, testPoints);

		formCluster(no_testPoints, testPoints, newCluster);
		calculateThreshold(no_testPoints, testPoints, threshold);
		//markPointsIntra(init_no_points, testDeck , clusternumber);
		markPoints(clusternumber, newCluster, threshold);

		Clusters.push_back(newCluster);

		if (testPoints)
		{
			delete[] testPoints;
			testPoints = NULL;
		}
	} while (!isAllMarkedAtleastOnce());

	printPointsWithClusters();

	return SUCCESS;
}