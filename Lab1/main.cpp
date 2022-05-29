#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<mpi.h>
#include<iostream>
using namespace std;
int N = 12;
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



int main(int argc, char* argv[]) {
	int num_procs, my_rank;
	double start = 0.0, stop = 0.0;
	long long per_procs = 0.0;
	long long result = 0.0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	if (my_rank == 0)
	{
		create();
		print();
	}
	start = MPI_Wtime();
	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < N; i++)
	{
		MPI_Bcast(mas[i], N, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
	}
	long long  det__;
	int sub_j, s;
	det__ = 0;
	s = 1;
	for (int i = my_rank; i < N; i += num_procs)
	{
		long long** subT;

		subT = new long long* [N - 1];
		sub_j = 0;
		for (int j = 0; j < N; j++)
			if (i != j)
				subT[sub_j++] = mas[j] + 1;
		s = i % 2 ? -1 : 1;
		det__ += s * mas[i][0] * det(subT, N - 1);
		delete[] subT;
	};
	MPI_Reduce(&det__, &result, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (my_rank == 0) {
		cout << "the sum of mpi is " << result << endl;
		stop = MPI_Wtime();
		cout << "the time of mpi is " << stop - start << endl;
	}
	MPI_Finalize();
	return 0;

}