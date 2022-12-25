#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

double F(vector<double> x) {
	return pow(x[0] - 2, 2) + pow(x[1] - 7, 2) + pow(x[2] + 11, 2);
}
//Решение -2 10 -20

double h = 0.0001;
vector<double> dF1(vector<double> x){
	vector<double> temp1(x.size());
	vector<double> temp2(x.size());
	vector<double> res(x.size());
	int n = x.size(), i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (j == i) {
				temp1[j] = x[j] + h;
				temp2[j] = x[j] - h;
			}
			else {
				temp1[j] = x[j];
				temp2[j] = x[j];
			}
		}
		res[i] = (F(temp1) - F(temp2)) / (2 * h);
	}
	return res;
}
double** dF2(vector<double> x){
	double** res;
	vector<double> temp1(x.size());
	vector<double> temp2(x.size());
	vector<double> temp3(x.size());
	vector<double> temp4(x.size());
	int i, j, k, n;
	n = x.size();

	res = new double* [n];
	for (i = 0; i < n; i++)
		res[i] = new double[n];

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) {
				for (k = 0; k < n; k++) {
					if (k == j) {
						temp1[k] = x[k] + h;
						temp2[k] = x[k] - h;
					}
					else {
						temp1[k] = x[k];
						temp2[k] = x[k];
					}
				}
				res[i][j] = (F(temp1) - 2 * F(x) + F(temp2)) / (h * h);
			}
			else {
				for (k = 0; k < n; k++) {
					if (k == i) {
						temp1[k] = x[k] + h;
						temp2[k] = x[k] + h;
						temp3[k] = x[k] - h;
						temp4[k] = x[k] - h;
					}
					else if (k == j) {
						temp1[k] = x[k] + h;
						temp2[k] = x[k] - h;
						temp3[k] = x[k] + h;
						temp4[k] = x[k] - h;
					}
					else {
						temp1[k] = x[k];
						temp2[k] = x[k];
						temp3[k] = x[k];
						temp4[k] = x[k];
					}
				}
				res[i][j] = (F(temp1) - F(temp2) - F(temp3) + F(temp4)) / (4 * h * h);
				res[j][i] = (F(temp1) - F(temp2) - F(temp3) + F(temp4)) / (4 * h * h);
			}
		}
	}
	return res;
}
vector<double> Gradient(vector<double> x){
	return dF1(x);
}
double Norm(vector<double> gradient) {
	double sum = 0;
	int n = gradient.size();
	for (int i = 0; i < n; i++)
		sum += gradient[i] * gradient[i];
	return sqrt(sum);
}
double* SimpleIteration(double** a, double* y, int n)
{
	double* res = new double[n];
	int i, j;


	for (i = 0; i < n; i++)
	{
		res[i] = y[i] / a[i][i];
	}

	double eps = 0.0001;
	double* Xn = new double[n];

	do {
		for (i = 0; i < n; i++) {
			Xn[i] = y[i] / a[i][i];
			for (j = 0; j < n; j++) {
				if (i == j)
					continue;
				else {
					Xn[i] -= a[i][j] / a[i][i] * res[j];
				}
			}
		}

		bool flag = true;
		for (i = 0; i < n - 1; i++) {
			if (abs(Xn[i] - res[i]) > eps) {
				flag = false;
				break;
			}
		}

		for (i = 0; i < n; i++) {
			res[i] = Xn[i];
		}

		if (flag)
			break;
	} while (1);

	return res;
}
double** InvMatr(double** a, int n)
{
	double** res;
	double* y = new double[n];
	double* itr;
	int i, j, k;

	res = new double* [n];
	for (i = 0; i < n; i++)
	{
		res[i] = new double[n];
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				y[j] = 1;
			}
			else
			{
				y[j] = 0;
			}
		}
		itr = SimpleIteration(a, y, n);
		for (k = 0; k < n; k++)
		{
			res[k][i] = itr[k];
		}
	}

	return res;
}
vector<double> Sk(double** H, double lambda, double** I, vector<double> gradient, int n) {
	int i, j;
	double** InvMatrix;
	double sum = 0;
	vector<double> s(n);
	for (i = 0; i < n; i++)
		I[i][i] *= lambda;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			H[i][j] += I[i][j];
			if (i == j) I[i][j] = 1;
			else I[i][j] = 0;
		}
	}
	InvMatrix = InvMatr(H, n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			InvMatrix[i][j] *= -1;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			sum += InvMatrix[i][j] * gradient[j];
		s[i] = sum;
		sum = 0;
	}
	return s;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	vector<double> x;
	vector<double> gradient;
	vector<double> way;
	int i, n;
	double num, e, lambda = 10000;
	double** H; double** I;
	bool flag = true;
	int MaxIteration, Iteration = 0;

	cout << "Введите размерность: ";
	cin >> n;
	cout << "Введите точку: ";
	for (i = 0; i < n; i++) {
		cin >> num;
		x.push_back(num);
	}
	cout << "Введите точность: ";
	cin >> e;
	cout << "Введите максимальное количество итераций: ";
	cin >> MaxIteration;

	I = new double* [n];
	for (i = 0; i < n; i++) {
		I[i] = new double [n];
	}

	for (i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) I[i][j] = 1;
			else I[i][j] = 0;
		}
	}

	while (true) {
		gradient = Gradient(x);
		if (Norm(gradient) < e && flag)
			break;
		if (MaxIteration < Iteration && flag)
			break;
		H = dF2(x);
		way = Sk(H, lambda, I, gradient, n);

		cout << "\nТочка: ";
		for (i = 0; i < n; i++)
			cout << x[i] << "\t";
		cout << "\nНаправление: ";
		for (i = 0; i < n; i++)
			cout << way[i] << "\t";
		cout << endl;
        cout << "========================================================";
		double temp = F(x);
		for (i = 0; i < n; i++)
			x[i] += way[i];
		if (F(x) < temp){
			flag = true;
			lambda /= 2;
			Iteration++;
		}
		else {
			flag = false;
			lambda *= 2;
		}
		
	}
	cout << endl;
	cout << "Точка решения: ";
	for (i = 0; i < n; i++)
		cout << x[i] << "\t";
	cout << endl;
	cout << "Количество итераций: " << Iteration << endl;
	return 0;
}