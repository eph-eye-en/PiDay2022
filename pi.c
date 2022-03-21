//Calculate a^b mod m by binary exponentiation
unsigned int binModExp(unsigned int a, unsigned int b, unsigned int m) {
	int res = 1;
	while(b > 0) {
		if(b % 2 == 1)
			res = ((unsigned long)res * a) % m;	//unsigned long avoids overflow
		a = ((unsigned long)a * a) % m;
		b >>= 1;
	}
	return res;
}

//Calculate a summation from the BBP digit extraction formula
double bbpSum(int n, int j) {
	double s = 0;
	for(int k = 0; k <= n; k++)
		s += (double)binModExp(16, n - k, 8 * k + j) / (8 * k + j);
		//s += (double)expm(n - k, 8 * k + j) / (8 * k + j);
	long numRecip = 16;
	int denom = 8 * (n+1) + j;
	double eps = 1e-6;
	double frac;
	while((frac = 1.0 / (numRecip * denom)) >= eps) {
		s += frac;
		numRecip *= 16;
		denom += 8;
	}
	return s;
}

//Return largest int less than or equal to x
int intFloor(double x) {
	int f = (int)x;
	if((double)f == x || x >= 0)
		return f;
	else
		return f - 1;
}

//Return the nth (0-based) hex decimal place of pi
int nthDigit(int n) {
	return (unsigned int)intFloor(16 * (4 * bbpSum(n, 1) - 2 * bbpSum(n, 4)
		- bbpSum(n, 5) - bbpSum(n, 6))) % 16;
}