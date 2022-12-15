using namespace std;
#include <iostream>
#include <cmath>

double f1(double xa, double ya)
{
	return 2*xa;
}

int main()
{
	int n = 20;
	double a = 0, b = 4, k1, k2, k3, k4;
	double h = (a + b) / n;
	double y11[21], x[21], y1[21];
	int i = 0;
	x[0] = a;
	y1[0] = 1;
	while (i < 3)
	{
		k1 = h * f1(x[i], y1[i]);
		k2 = h * f1(x[i] + h / 2.0, y1[i] + k1 / 2.0);
		k3 = h * f1(x[i] + h / 2.0, y1[i] + k2 / 2.0);
		k4 = h * f1(x[i] + h, y1[i] + k3);
		y1[i + 1] = y1[i] + ((k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0);

		x[i + 1] = x[i] + h;

		i = i + 1;

	}

	for (int i = 3; n > i; i++)
	{

		x[i + 1] = x[i] + h;

		y11[i] = y1[i - 3] + (4.0 * h) / 3.0 * (2.0 * f1(x[i], y1[i]) - f1(x[i - 1], y1[i - 1]) + 2.0 * f1(x[i - 2], y1[i - 2]));

		y1[i + 1] = y1[i - 1] + (h / 3.0) * (f1(x[i + 1], y11[i + 1]) + 4.0 * f1(x[i], y1[i]) + f1(x[i - 1], y1[i - 1]));

		cout << "================" << endl;
		cout << "y[i]: " << y1[i] << endl;
	}
}