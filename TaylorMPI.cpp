#include "pch.h"
#include "mpi.h"
#include <iostream>
#include <windows.h>
using namespace std;
//e^x=∑((x^n)/n!)
double Fact(int n)
{
	if (n == 0)
		return 1;
	else
		return n * Fact(n - 1);
}

int main(int argc, char *argv[])
{
	SetConsoleOutputCP(1251);
	int n;
	int myid;
	int numprocs;
	int i;
	int rc;
	long double drob, drobSum = 0, Result, sum;
	double startwtime = 0.0;
	double endwtime;

	n = 100000;
	//n = atoi(argv[1]);

	if (rc = MPI_Init(&argc, &argv)) //передает всем процессам аргументы main
	{
		cout << "Ошибка запуска, выполнение остановлено " << endl;
		MPI_Abort(MPI_COMM_WORLD, rc); //Аварийное завершение работы всех процессов.
	}

	MPI_Comm_size(MPI_COMM_WORLD, &numprocs); //Определение общего числа параллельных процессов 
	MPI_Comm_rank(MPI_COMM_WORLD, &myid); //Определение номера процесса


	if (myid == 0)
	{

		startwtime = MPI_Wtime();
	}
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); //Рассылка сообщения от процесса всем процессам, включая рассылающий процесс

	for (i = myid; i <= n; i += numprocs)
	{
		drob = 1 / Fact(i);
		drobSum += drob;
	}

	MPI_Reduce(&drobSum, &Result, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); 
	cout.precision(20);
	if (myid == 0)
	{
		cout << Result << endl;
		endwtime = MPI_Wtime();
		cout << (endwtime - startwtime)  << endl;
	}

	MPI_Finalize();
	return 0;
}