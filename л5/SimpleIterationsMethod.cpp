#include <iostream>

using namespace std;

int main() {
	system("chcp 1251");
	system("cls");

	const int n = 5;

	double A[n][n], b[n];

	A[0][0] = 24; A[0][1] = 2; A[0][2] = 2; A[0][3] = 2; A[0][4] = 2;
	A[1][0] = 1; A[1][1] = 24; A[1][2] = 1; A[1][3] = 3; A[1][4] = 2;
	A[2][0] = 2; A[2][1] = 1; A[2][2] = 32; A[2][3] = 1; A[2][4] = 3;
	A[3][0] = 2; A[3][1] = 2; A[3][2] = 2; A[3][3] = 24; A[3][4] = 3;
	A[4][0] = 3; A[4][1] = 1; A[4][2] = 1; A[4][3] = 1; A[4][4] = 24;

	b[0] = 30; b[1] = 55; b[2] = -28; b[3] = 73; b[4] = -17;

	cout << "A: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "B: " << endl;
	for (int i = 0; i < n; i++) {
		cout << b[i] << " ";
	}
	cout << endl << endl;

	double eps = 0.0001;
	double X[n], Xn[n];

	// Íà÷àëüíîå ïðèáëèæåíèå õ
	cout << "Íà÷àëüíîå ïðèáëèæåíèå:" << endl;
	for (int i = 0; i < 5; i++)
	{
		X[i] = b[i] / A[i][i];
		cout << X[i] << "  ";
	}
	cout << endl << endl;

	cout << "Òî÷íîñòü: " << eps << endl << endl;

	int counter = 0;

	double C[n][n];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (j == i) {
				C[i][j] = 0;
			}
			else {
				C[i][j] = A[i][j] / A[i][i];
			}
		}
	}

	// Ìåòîä ïðîñòîé èòåðàöèè
	do {
		for (int i = 0; i < 5; i++)
		{
			Xn[i] = b[i] / A[i][i];
			for (int j = 0; j < 5; j++)
			{
				Xn[i] -= C[i][j] * X[j];
			}
		}

		bool flag = true;

		for (int i = 0; i < 4; i++)
		{
			if (abs(Xn[i] - X[i]) > eps)
			{
				flag = false;
				break;
			}
		}

		for (int i = 0; i < 5; i++)
		{
			X[i] = Xn[i];
		}

		if (flag)
		{
			break;
		}

		counter++;

	} while (true);

	// Ââîä ìàññèâà X íà ýêðàí
	cout << "Ìåòîä ïðîñòûõ èòåðàöèé:" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << X[i] << "  ";
	}
	cout << endl << endl;

	double sum = 0;

	// Ïðîâåðêà êîðíÿ
	cout << "Ïðîâåðêà:" << endl;
	for (int i = 0; i < 5; i++)
	{
		sum = 0;
		for (int j = 0; j < 5; j++)
		{
			sum = sum + A[i][j] * X[j];
		}
		cout << sum << " ";
	}
	cout << endl << endl;

	cout << "Êîë-âî èòåðàöèé: " << counter << endl;

	return 0;
}