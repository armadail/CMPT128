#include <iostream>
#include <iomanip>
using namespace std;

double  mySum(double  X, unsigned  int  N);

int main()
{
	double x = 0.333;
	for (int i = 0; i < 9; i++)
	{
		cout << setw(19) << x;
		cout << setw(19) << mySum(x, 3);
		cout << setw(19) << 1 / (mySum(x, 5));
		cout << setw(19) << mySum(x, 7);
		cout << endl;
		x += 1;
	}
	return 0;

}

double  mySum(double  X, unsigned  int  N)
{
	if (N == 0)
		return X;
	else
	{
		return X + mySum(X + 1, N - 1);
	}
}