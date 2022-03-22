#include <stdint.h>

//Calculate a^b mod m by binary exponentiation
uint32_t binModExp(uint16_t a, uint16_t b, uint32_t m) {
	int32_t res = 1;
	while(b > 0) {
		if(b % 2 == 1)
			res = ((uint64_t)res * a) % m;	//Use more bits to avoid overflow
		a = ((uint64_t)a * a) % m;
		b >>= 1;
	}
	return res;
}

//Return largest int less than or equal to x
int16_t intFloor(float x) {
	int16_t f = (int16_t)x;	//Truncate x
	if((float)f == x || x >= 0)
		return f;	//Truncation should have produced correct value
	else
		return f - 1;	//Adjust because truncation rounded the wrong way
}

//Calculate a summation from the BBP digit extraction formula (mod 1)
float bbpSum(int16_t n, int16_t j) {
	float s = 0;
	for(int16_t k = 0; k <= n; k++) {
		s += (float)binModExp(16, n - k, 8 * (uint32_t)k + j) / (8 * k + j);
		s -= intFloor(s);
	}
	uint64_t numRecip = 16;	//Use more bits because these numbers get big
	uint32_t denom = 8 * ((uint32_t)n+1) + j;
	float eps = 1e-6;
	float frac;
	while((frac = 1.0 / (numRecip * denom)) >= eps) {
		s += frac;
		numRecip *= 16;
		denom += 8;
	}
	return s;
}

//Return the nth (0-based) hex decimal place of pi
int16_t nthDigit(int16_t n) {
	return (uint16_t)intFloor(16 * (4 * bbpSum(n, 1) - 2 * bbpSum(n, 4)
		- bbpSum(n, 5) - bbpSum(n, 6))) % 16;
}