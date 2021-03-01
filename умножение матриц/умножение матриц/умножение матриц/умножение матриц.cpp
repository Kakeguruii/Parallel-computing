// умножение матриц.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include<iostream>
#include <cstdlib>
#include<stdlib.h>
#include <omp.h>
#include<ctime>

using namespace std;


int main()
{
	setlocale(LC_ALL, "rus");
	system("color 60");
	const int n = 20, A = -25, B = 25;
	int a[n][n], b[n][n], c[n][n];
	int i, j, k, x, y, z, f;
	double t;
	cout << "Введите количество строк первой матрицы:" << ends;                //ввод колва строк и столбцов двух матриц
	cin >> x;
	cout << "Введите количество столбцов первой матрицы:" << ends;
	cin >> y;
	cout << "Введите количество строк второй матрицы:" << ends;
	cin >> z;
	cout << "Введите количество столбцов первой матрицы:" << ends;
	cin >> f;
	if ((x != f) && (y != z))
		cout << "Эти матрицы невозможно перемножить";           //проверка условия, необходимого для перемножения матриц
	/*srand(time(0));*/
	for (i = 0; i < x; i++)
		for (j = 0; j < y; j++)
			/*a[i][j] = rand() % (B - A + 1) + A;*/     //ввод первой матрицы
			a[i][j] = 1;

	/*srand(time(0));*/
	for (i = 0; i < z; i++)
		for (j = 0; j < f; j++)
			/*b[i][j] = rand() % (B - A + 1) + A; */    //ввод второй матрицы
			b[i][j] = 1;

	for (i = 0; i < x; i++)
		for (j = 0; j < f; j++)
			c[i][j] = 0;


	//ПОСЛЕДОВАТЕЛЬНЫЙ АЛГОРИТМ
	t = omp_get_wtime();
	for (i = 0; i < x; i++)
	{
		for (j = 0; j < f; j++)
		{
			c[i][j] = 0;
			for (k = 0; k < z; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
	t = omp_get_wtime() - t;
	cout << endl << "Умножение матриц последовательным алгоритом: " << endl << endl;
	for (i = 0; i < x; i++)
	{
		for (j = 0; j < f; j++)
		{
			cout << c[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl << "Время выполнения последовательного алгоритма: " << fixed << t << endl << endl;
	///////////////////////////////////////////////////////////////////////////////////////








	//МАШИННЫЙ АЛГОРИТМ////////////////////////////////////////////////////////////////////


	t = omp_get_wtime();
#pragma omp parallel shared(a,b,c,x,f,z) private(i,j)
	{

#pragma omp for
		for (i = 0; i < x; i++)
		{
			for (j = 0; j < f; j++)
			{
				c[i][j] = 0;
				for (k = 0; k < z; k++)
					c[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	t = omp_get_wtime() - t;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << endl << "Умножение матриц машинным алгоритом: " << endl << endl;
	for (i = 0; i < x; i++)
	{
		for (j = 0; j < f; j++)
		{
			cout << c[i][j] << "  ";
		}
		cout << endl;
	}

	cout << endl << "Время: " << t << endl << endl;



}

