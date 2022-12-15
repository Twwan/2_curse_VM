#include <iostream>
#include<cmath>

using namespace std;

double SourceFunc(double x)
{
	return 0.5 * sqrt(x) + 0.25 * x * x - x;
}

double CalcZ(int i, double* arrX, double h) // Принимает индекс для поиска b с индексом i+1, массив х и длину шага
{
	//cout << "Z = " << ((2 * (SourceFunc(arrX[i + 1]) - SourceFunc(arrX[i])) / h)) << endl;
	return ((2 * (SourceFunc(arrX[i + 1]) - SourceFunc(arrX[i])) / h));
}

double PolinomS(int i, double x, double* arrX, double** arrK)
{
	return (arrK[0][i] + arrK[1][i] * (x - arrX[i]) + arrK[2][i] * (x - arrX[i]) * (x - arrX[i]));
}

int main()
{
	setlocale(LC_ALL, "Rus");

	cout << "Введите границы промежутка: ";

	double a, b; // Границы промежутка

	cin >> a >> b;

	cout << "Введите количество интервалов: ";

	int n; // Количество интервалов

	cin >> n;

	double** arrK = new double* [3]; // Массив Коэффициентов 3*n

	for (int i = 0; i < 3; i++)
	{
		arrK[i] = new double[n + 1];
	}

	double* arrX = new double[n + 1]; // Массив Х n+1 размерности

	double h = (b - a) / n; // Длина шага 

	double x0 = a; // Начальный х0
	// Заполнение массива значений х
	for (int i = 0; i < n + 1; i++)
	{
		arrX[i] = x0;
		x0 = x0 + h;
	}
	// Заполнение коэффициента а
	for (int i = 0; i < n + 1; i++)
	{
		arrK[0][i] = SourceFunc(arrX[i]);
	}

	// Расчёт коэффициента b

	arrK[1][0] = 0; // b0 = A0 = 0

	for (int i = 0; i < n; i++)
	{
		arrK[1][i + 1] = CalcZ(i, arrX, h) - arrK[1][i];
	}

	// Вывод массива x

	for (int i = 0; i < n + 1; i++)
	{
		//cout << arrX[i] << "\t";
	}

	cout << endl;

	// Расчёт коэффициента с

	for (int i = 0; i < n; i++)
	{
		arrK[2][i] = (arrK[1][i + 1] - arrK[1][i]) / (2 * h);
	}

	arrK[2][n] = 0;

	// Поиск значения y в точке x 

	cout << "Введите значение x ";

	double x;

	cin >> x;

	double index = trunc((x - a) / h);

	//cout << "Index " << index << endl;

	// Вывод массива коэффициентов

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			//cout << arrK[i][j] << "\t";
		}
		//cout << endl;
	}

	cout << "S = " << PolinomS(index, x, arrX, arrK) << endl;

	cout << "f(x) = " << SourceFunc(x) << endl;

	// Удаление массива Коэффициентов
	for (int i = 0; i < 3; i++)
	{
		delete arrK[i];
	}

	delete[] arrK;

	delete[] arrX;

	return 0;
}