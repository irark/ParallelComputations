#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<vector>
#include<time.h>
#include<omp.h>
#include<iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;



int N = 13;


long long mas[100][100];
double det(long long** T, int n)
{
	long long  det__;
	int sub_j, s;
	long long** subT;
	switch (n)
	{
	case 1:
		return T[0][0];
	case 2:
		return T[0][0] * T[1][1] - T[0][1] * T[1][0];
	default:
		subT = new long long* [n - 1];
		det__ = 0;
		s = 1;
		for (int i = 0; i < n; i++)
		{
			sub_j = 0;
			for (int j = 0; j < n; j++)
				if (i != j)
					subT[sub_j++] = T[j] + 1;

			det__ = det__ + s * T[i][0] * det(subT, n - 1);
			s = -s;
		};
		delete[] subT;
		return det__;
	};
};

void create() {
	srand(123);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			mas[i][j] = (int)(rand() % 5);
	}
}

void print()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << mas[i][j] << " ";
		cout << endl;
	}
}


int main() {
	create();
	print();
	auto start = steady_clock::now();
	long long  det__;
	int sub_j, s;
	long long** subT;
	subT = new long long* [N - 1];
	det__ = 0;
	s = 1;
	for (int i = 0; i < N; i++)
	{
		sub_j = 0;
		for (int j = 0; j < N; j++)
			if (i != j)
				subT[sub_j++] = mas[j] + 1;

		det__ += s * mas[i][0] * det(subT, N - 1);
		s = -s;
	};
	delete[] subT;

	auto stop = steady_clock::now();
	cout << "the sum of sync is " << det__ << endl;
	cout << "the time of sync is " << (double)duration_cast<microseconds>(stop - start).count() / 1000000.0 << endl;
	return 0;
}