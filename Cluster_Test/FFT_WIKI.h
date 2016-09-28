#include <iostream>

#include <iostream>
#include <complex>
#define MAX 500

using namespace std;

#define M_PI 3.1415926535897932384
#define SUCCESS		0
#define FAIL		1


namespace FFT_WIKI
{
//private:

	int log2(int N);
	int check(int n);
	int reverse(int N, int n);
	void ordina(complex<double>* f1, int N);
	void transform(complex<double>* f, int N);
	void FFT(complex<double>* f, int N, double d);

//public :

	int fft_test1(int totDim, int* input, double* output);
};