#include "stdafx.h"
#include "FFT_WIKI.h"

int FFT_WIKI::log2(int N)    /*function to calculate the log2(.) of int numbers*/
{
	int k = N, i = 0;
	while (k) {
		k >>= 1;
		i++;
	}
	return i - 1;
}

int FFT_WIKI::check(int n)    //checking if the number of element is a power of 2
{
	return n > 0 && (n & (n - 1)) == 0;
}

int FFT_WIKI::reverse(int N, int n)    //calculating revers number
{
	int j, p = 0;
	for (j = 1; j <= log2(N); j++) {
		if (n & (1 << (log2(N) - j)))
			p |= 1 << (j - 1);
	}
	return p;
}

void FFT_WIKI::ordina(complex<double>* f1, int N) //using the reverse order in the array
{
	complex<double> f2[MAX];
	for (int i = 0; i < N; i++)
		f2[i] = f1[reverse(N, i)];
	for (int j = 0; j < N; j++)
		f1[j] = f2[j];
}

void FFT_WIKI::transform(complex<double>* f, int N) //
{
	ordina(f, N);    //first: reverse order
	complex<double> *W;
	W = (complex<double> *)malloc(N / 2 * sizeof(complex<double>));
	W[1] = polar(1., -2. * M_PI / N);
	W[0] = 1;
	for (int i = 2; i < N / 2; i++)
		W[i] = pow(W[1], i);
	int n = 1;
	int a = N / 2;
	for (int j = 0; j < log2(N); j++) {
		for (int i = 0; i < N; i++) {
			if (!(i & n)) {
				complex<double> temp = f[i];
				complex<double> Temp = W[(i * a) % (n * a)] * f[i + n];
				f[i] = temp + Temp;
				f[i + n] = temp - Temp;
			}
		}
		n *= 2;
		a = a / 2;
	}
}

void FFT_WIKI::FFT(complex<double>* f, int N, double d)
{
	transform(f, N);
	for (int i = 0; i < N; i++)
		f[i] *= d; //multiplying by step
}

int FFT_WIKI::fft_test1(int totDim, int* input, double* output)
{
	complex<double> vec[MAX];

	for (int i = 0; i < totDim; i++) 
	{
		std::complex<double> temp(input[i], 0);
		vec[i] = temp;
		vec[2 * totDim - i - 1] = temp;
	}

	FFT_WIKI::FFT(vec, 2*totDim, 1);		//just write 1 in order to have the same results of matlab fft(.)

	int k = 0;
	for (int i = 1; i < 2 * totDim; i = i + 2)
	{
		output[k] = vec[i].real();
	//	std::cout << output[k] << " ";
		k++;
	}

	return SUCCESS;
}


