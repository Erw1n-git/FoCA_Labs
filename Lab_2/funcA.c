#include "funcA.h"

double funcA(double x, double y, double z)
{
	double divisible = cbrt(8 + pow(std::abs(x-y), 2) + 1);
	double divisor = pow(x, 2) + pow(y, 2) + 2;
	return divisible/divisor;
}
