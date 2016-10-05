#pragma once

#include <vector>

#define SUCCESS		0
#define FAIL		1

#define INIT_CLUSTERPOINTS		10

#define MIN_INIT_CLUSTERPOINTS	3

#define HARD_CLUSTERING_FACTOR	2

#define MARK_POINTS_FACTOR		1


#define RANDOM(min, max)  min + rand() % (max - min + 1) //range : [min, max] . Seeding done in constructor. [INTEGER]

#define FLOAT_RANDOM(min, max)  min + (rand() / ( double(RAND_MAX) / (max - min )))  //range : [min, max] . Seeding done in constructor.[DOUBLE]

#define DOUBLE_RANDOM	 ((double)rand() / (double)RAND_MAX)	//range : [0, 1] . Seeding done in constructor.[DOUBLE]


#define square(x)  ((x)*(x))
#define mod(x)  (x<0.0)? (-1 * x) : (x);
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX_NO(a,b) (((a)>(b))?(a):(b))

#define int int
//typedef int int;

struct point_clusters {
	int clusterNumber;
	double percision;
};

struct node {
	int no = -1;
	//std::vector<int> clusterNos;
	std::vector<point_clusters> clusterNos;
	//int *clusterNos = NULL;
	int numberOfAssignedClusters = 0;
	int *dim = NULL;
};

//const double epsilon = pow(10.0, -8);

#define UNREFERENCED_PARAMETER(P) (P)





