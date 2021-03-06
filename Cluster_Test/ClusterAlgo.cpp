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

	sigClusters = new SignificantClusters[_totSample];

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

	if (sigClusters)
	{
		delete[] sigClusters;
		sigClusters = NULL;
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
		//std::cout <<std::endl;
		//std::cout << i << std::endl;
		FFT_WIKI::fft_test1(totDim, Nodes[i].dim, fftOfPoints[i].samples);
		//std::cout << std::endl;
	//	for (int j = 0; j < totDim; j++)
	//	{
	//		std::cout << fftOfPoints[i].samples[j] << " ";
	//	}
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
		int temp = RANDOM(0, totSample - 1);

	//	if (Nodes[temp].numberOfAssignedClusters > 0)	continue;

	//	if (isEvaluated(temp))	continue;

		for (i = 0; i < k; i++)
		{
			if (testPoints[i] == temp)	break;
		}

		if (k == i)		testPoints[k++] = temp;

	} while (k < no_testPoints);

	return SUCCESS;
}

int ClusterAlgo::hard_clustering(int totDim, int *Input, int init_no_points, int *Output, int& out_init_no_points)
{
	//
	double min_dis = 0;
	int a = -1, b = -1;
	int factor = HARD_CLUSTERING_FACTOR;

	for (int i = 0; i < init_no_points; i++)
	{
		for (int j = i + 1; j < init_no_points; j++)
		{
			double dis = 0;

			for (int k = 0; k < totDim; k++)
			{
				dis += std::pow(Nodes[Input[i]].dim[k] - Nodes[Input[j]].dim[k], 2);
			}

			dis = std::sqrt(dis);

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
	double radius = min_dis;
	node CENTROID;
	CENTROID.dim = new double[totDim];

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
		double dis = 0;

		for (int k = 0; k < totDim; k++)
		{
			dis += std::pow(Nodes[Input[j]].dim[k] - CENTROID.dim[k], 2);
		} 
		dis = std::sqrt(dis);

		if (dis <= factor * radius)
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
	//First euclidean distance calculate and then fft
	double *avg_dim = new double[totDim];

	for (int i = 0; i < totDim; i++)
	{
		double sum = 0.0;
		for (int j = 0; j < no_testPoints; j++)
		{
			sum += Nodes[testPoints[j]].dim[i];
		}
		sum /= no_testPoints;
		avg_dim[i] = sum;
	}

	FFT_WIKI::fft_test1(totDim, avg_dim, newCluster);

	//Take average of fft
	/*double *avg_dim = new double[totDim];

	for (int i = 0; i < totDim; i++)
	{
		double sum = 0.0;
		for (int j = 0; j < no_testPoints; j++)
		{
			sum += fftOfPoints[testPoints[i]].samples[j];
		}
		sum /= no_testPoints;
		avg_dim[i] = sum;
	}*/

	return SUCCESS;
}

int ClusterAlgo::calculateThreshold(int &no_testPoints, int * testPoints, double& threshold)
{
	double min_dis = 0.0;

	for (int i = 0; i < no_testPoints; i++)
	{
		for (int j = i + 1 ; j < no_testPoints; j++)
		{
			double dis = 0;

			for (int k = 0; k < totDim; k++)
			{
				dis += std::pow(fftOfPoints[testPoints[i]].samples[k] - fftOfPoints[testPoints[j]].samples[k], 2);
			}

			dis = std::sqrt(dis);

			if ((dis < min_dis) || (i == 0))
			{
				min_dis = dis;
			}
		}
	}
	threshold = min_dis;

	return SUCCESS;
}

int ClusterAlgo::markPoints_dotproduct(int clusterNos, double *newCluster, double threshold, int &no_testPoints, int * testPoints)
{
	int flag = 0;
	double factor = 0.995;// MARK_POINTS_FACTOR;
	std::vector<int> pos;
	int inddx = RANDOM(0, no_testPoints - 1);
	double *rand_center = fftOfPoints[testPoints[inddx]].samples;
	for (int i = 0; i < totSample; i++)
	{
		double score = 0.0;
		double a = 0.0, b = 0.0;
		for (int j = 0; j < totDim; j++)
		{
			/*score += (fftOfPoints[i].samples[j] * newCluster[j]);
			a += std::pow(fftOfPoints[i].samples[j], 2);
			b += std::pow(newCluster[j], 2);*/
			score += (fftOfPoints[i].samples[j] * rand_center[j]);
			a += std::pow(fftOfPoints[i].samples[j], 2);
			b += std::pow(rand_center[j], 2);
		}
		a = std::sqrt(a);
		b = std::sqrt(b);
		score /= (a*b);
	//	score /= (a - b);
		score = mod(score);
		//double diff = a - b;
		//diff /= (a*b);
		//diff = mod(diff);
		//if ((score * diff) >= factor)
		if (score >= factor)
		{
			double temp = score - factor;
			temp /= factor;
			flag++;
			Nodes[i].clusterNos.push_back({ clusterNos, temp });				// +Nodes[i].numberOfAssignedClusters;
			Nodes[i].numberOfAssignedClusters++;
			pos.push_back(i);
		}
	}

	if (MIN_INIT_CLUSTERPOINTS >= flag)
	{
		return FAIL;
	}
	else
	{
		//std::cout << std::endl;
		//std::cout << std::endl;
		//std::cout << "Cluster No " << clusterNos << "  ::   ";
		//std::cout << std::endl << "==============================" << std::endl;
		//std::cout << "Total number of points in this cluster :: " << flag << std::endl << " Points are :: ";
		//for (int i = 0; i < pos.size(); i++)
		//{
		//	std::cout << " " << pos[i];
		////	std::cout << " Per: " << Nodes[pos[i]].clusterNos[Nodes[pos[i]].numberOfAssignedClusters - 1].percision;
		//}
		std::vector<int>().swap(pos);
	}
	return SUCCESS;
}

int ClusterAlgo::markPoints(int clusterNos, double *newCluster, double threshold)
{
	int flag = 0;
	int factor = MARK_POINTS_FACTOR;
	std::vector<int> pos;
	for (int i = 0; i < totSample; i++)
	{
		double score = 0.0;
		for (int j = 0; j < totDim; j++)
		{
			score += std::pow(fftOfPoints[i].samples[j] - newCluster[j], 2);
		}
		score = std::sqrt(score);

		if (score <= factor*threshold)
		{
			double temp = factor*threshold - score;
			temp /= factor*threshold;
			flag++;
			Nodes[i].clusterNos.push_back({ clusterNos, temp });				// +Nodes[i].numberOfAssignedClusters;
			Nodes[i].numberOfAssignedClusters++;
			pos.push_back(i);
		}
	}
	
	if (MIN_INIT_CLUSTERPOINTS >= flag)
	{
		return FAIL;
	}
	else
	{
		/*std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Cluster No " << clusterNos << "  ::   ";
		std::cout << std::endl << "==============================" << std::endl;
		std::cout << "Total number of points in this cluster :: " << flag << std::endl << " Points are :: ";
		for (int i = 0; i < pos.size(); i++)
		{
			std::cout << " " << pos[i];
			std::cout << " Per: " << Nodes[pos[i]].clusterNos[Nodes[pos[i]].numberOfAssignedClusters - 1].percision;
		}*/
		std::vector<int>().swap(pos);
	}
	return SUCCESS;
}

int ClusterAlgo::printPointsWithClusters()
{
	/*for (int i = 0; i < totSample; i++)
	{
		std::cout << "Point No : " << Nodes[i].no << "     ";
		for (int j = 0; j < Nodes[i].numberOfAssignedClusters; j++)
		{
			std::cout << Nodes[i].clusterNos[j] << "   ";
		}
		std::cout << std::endl;
	}*/
	int tot_clusters = Clusters.size() ;
	int totSamples = 0;
	for (int i = 0; i < tot_clusters; i++)
	{
		totSamples = 0;		
		std::cout << "Cluster No " << i << "  :   ";
		for (int k = 0; k < totSample; k++)
		{
			for (int j = 0; j < Nodes[k].numberOfAssignedClusters; j++)
			{
				if (i == Nodes[k].clusterNos[j].clusterNumber)
				{
					totSamples++;
					//std::cout << Nodes[k].no - 1 << "   ";
					break;
				}
			}			
		}
		std::cout << "Total number od points in this cluster : " << totSamples ;
		std::cout << std::endl;
	}
	return SUCCESS;
}

int ClusterAlgo::debugClusters()
{
	for (int k = 0; k < totSample; k++)
	{
		double max_per = 0.0;
		int indx = -1;

		for (int j = 0; j < Nodes[k].numberOfAssignedClusters; j++)
		{
			if (Nodes[k].clusterNos[j].percision > max_per)
			{
				indx = j;
			}
		}

		sigClusters[k].ClusterNumber = Nodes[k].clusterNos[indx].clusterNumber;
		sigClusters[k].percesion = Nodes[k].clusterNos[indx].percision;
		//std::cout << "Sample No : " << k << " Cluster : " << Nodes[k].clusterNos[indx].clusterNumber << std::endl;
	}
	return SUCCESS;
}

int ClusterAlgo::compressClusters()
{
	int i;
	int ClusterName;

	//ClusterFreq *ClusterFreqebcy = new ClusterFreq[];

	std::vector<ClusterFreq> ClusterFr;

	for (int k = 0; k < totSample; k++)
	{
		ClusterName = sigClusters[k].ClusterNumber;

		for (i = 0; i < ClusterFr.size(); i++)
		{
			if (ClusterName == ClusterFr[i].name)
			{
				ClusterFr[i].count++;
				break;
			}
		}
		if (i == ClusterFr.size())
		{
			ClusterFreq temp;
			temp.name = ClusterName;
			temp.count = 1;
			ClusterFr.push_back(temp);
		}
	}

	//find the one with minimum count
	int min_clusternumber = 0;
	int count = ClusterFr[0].count;

	for (i = 0; i < ClusterFr.size(); i++)
	{
		if (ClusterFr[i].count < count)
		{
			count = ClusterFr[i].count;
			min_clusternumber = ClusterFr[i].name;
		}
	}

	//find its alias
	int aliasClusterName = -1;
	double score = 0.0;
	double a, b;
	for (i = 0; i < ClusterFr.size(); i++)
	{
		double temp = 0.0;
		a = b = 0.0;
		
		if (ClusterFr[i].name != min_clusternumber)
		{
			for (int j = 0; j < totDim; j++)
			{
				temp += (Clusters[ClusterFr[i].name][j] * Clusters[min_clusternumber][j]);
				a += std::pow(Clusters[ClusterFr[i].name][j], 2);
				b += std::pow(Clusters[min_clusternumber][j], 2);
			}			
		}

		a = std::sqrt(a);
		b = std::sqrt(b);
		temp /= (a*b);
		//score /= (a - b);
		temp = mod(temp);

		if (temp > score)
		{
			score = temp;
			aliasClusterName = ClusterFr[i].name;
		}
	}

	//replace all with the alias
	for (int k = 0; k < totSample; k++)
	{
		if (sigClusters[k].ClusterNumber == min_clusternumber)	sigClusters[k].ClusterNumber = aliasClusterName;
	}

	if (ClusterFr.size() > 0)
	{
		std::vector<ClusterFreq>().swap(ClusterFr);
	}

	return SUCCESS;
}

bool ClusterAlgo::showResultsALL()
{
	for (int k = 0; k < totSample; k++)
	{
		std::cout << std::endl << "Sample No : " << k;
		for (int j = 0; j < Nodes[k].numberOfAssignedClusters; j++)
		{
			std::cout << " " << "C: " << Nodes[k].clusterNos[j].clusterNumber <<
				"P: " << Nodes[k].clusterNos[j].percision ;
		}		
	}
	return true;
}

bool ClusterAlgo::showResults()
{
	for (int k = 0; k < totSample; k++)
	{
		std::cout << "Sample No : " << k << " Cluster : " << sigClusters[k].ClusterNumber << std::endl;// <<
		//	"P: " << sigClusters[k].percesion << std::endl;
	}
	return true;
}

int ClusterAlgo::run()
{
	getFFTofAllPoints();
	int clusternumber = 0;
	do
	{
		int no_testPoints = INIT_CLUSTERPOINTS;
		int *testPoints = new int[no_testPoints];
		for (int i = 0; i < no_testPoints; i++) testPoints[i] = -1;
		double *newCluster = NULL;
		double threshold = 0.0;

		getRandomPoints(no_testPoints, testPoints);
		getSimilarPoints(no_testPoints, testPoints);

		if (no_testPoints >= MIN_INIT_CLUSTERPOINTS)
		{
			newCluster = new double[totDim];			
			formCluster(no_testPoints, testPoints, newCluster);
			calculateThreshold(no_testPoints, testPoints, threshold);
			//markPointsIntra(init_no_points, testDeck , clusternumber); 
			//if (SUCCESS == markPoints(clusternumber, newCluster, threshold))
			if (SUCCESS == markPoints_dotproduct(clusternumber, newCluster, threshold, no_testPoints, testPoints))
			{				
				Clusters.push_back(newCluster);
				clusternumber++;
			}			
		}

		if (testPoints)
		{
			delete[] testPoints;
			testPoints = NULL;
		}

		/*if (newCluster)
		{
			delete[] newCluster;
			newCluster = NULL;
		}*/

	} while (!isAllMarkedAtleastOnce());

	debugClusters();

	//printPointsWithClusters();

	return SUCCESS;
}