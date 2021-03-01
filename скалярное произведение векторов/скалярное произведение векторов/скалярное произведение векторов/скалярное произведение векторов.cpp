// скалярное произведение векторов.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include<iostream>
#include <cstdlib>
#include<stdlib.h>
#include <omp.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	int tid = 0;
	int i;
	int pr = 0;
	const int n = 100000;
	int a[n], b[n], res = 0;
	double t;


	for (i = 0; i < n; i++)
	{
		a[i] = 1; //rand()%n5
		b[i] = 1; //rand()%n;


	}
	t = omp_get_wtime();
	for (i = 0; i < n; i++)
	{
		pr += a[i] * b[i];
	}
	cout << "\nСкалярное произведение последовательного алгоритма: " << pr << endl;
	t = omp_get_wtime() - t;
	cout << "Время: " << t << endl << endl;


	double prod = 0;
	t = omp_get_wtime();
#pragma omp parallel shared(a,b,n) private(i)
	{
		float paralpr = 0;
#pragma omp for
		for (i = 0; i < n; i++)
			paralpr += a[i] * b[i];
		prod += paralpr;
	}
	t = omp_get_wtime() - t;
	cout << "Cкалярное произведение машинного параллельного алгоритма: " << prod << endl;
	cout << "Время: " << t << endl << endl;



	t = omp_get_wtime();
#pragma omp parallel num_threads(4) private (tid) shared(res)
	{
		int numt = omp_get_num_threads();
		// printé("\n numt= %d ", numt);
		int locres = 0;
		int kol = n / numt;
		tid = omp_get_thread_num();
		// printf("\n tid= %d ", tid);

		if (tid < numt - 1)
		{
			for (int i = 0; i < kol; i++)
			{
				locres += a[tid * kol + i] * b[tid * kol + i];
			}
			//printf("\n locres = %d",locres);
		}
		else
		{
			for (int i = 0; i < kol + n - kol * numt; i++)
			{
				locres += a[tid * kol + i] * b[tid * kol + i];
			}
			//printf("\n locres= %d",locres);
		}



#pragma omp critical
		res = res + locres;

	}

	t = omp_get_wtime() - t;
	cout << "Скалярное произведение ручного параллельного алгоритма: " << res << endl;
	cout << "Время: " << fixed << t << endl << endl;
	/*printf("\n Otvet= %d",res);
	printf("\n Time= %lf \n",t );*/

}
