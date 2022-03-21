#include <stdio.h>
//#include <math.h>
#include "pi.c"

void binModExpTest() {
	for(int b = 0; b < 20; b++)
		printf(" %x", b);
	printf("\n");
	for(int m = 1; m < 20; m++) {
		printf("%x", m);
		for(int b = 0; b < 20; b++) {
			printf(" %x", binModExp(16, b, m));
		}
		printf("\n");
	}
}

void bbpSumTest() {
	for(int n = 0; n < 10; n++) {
		double x = 4 * bbpSum(n, 1) - 2 * bbpSum(n, 4) - bbpSum(n, 5) - bbpSum(n, 6);
		printf("%f\t%x\t%x\n\n", x, (int)(x * 16*16*16*16),
			((unsigned int)intFloor(x * 16) % 16));
	}
}

void nthDigitTest() {
	for(int i = 0; i < 10000; i++) {
		printf("%x", nthDigit(i));
		if(i % 64 == 63)
			printf("\n");
	}
}

int main() {
	//binModExpTest();
	//bbpSumTest();
	//nthDigitTest();

	char values[] = { sizeof(char), sizeof(short), sizeof(int), sizeof(long),
		sizeof(long long) };
	for(int i = 0; i < sizeof(values); i++)
		printf("%i\n", values[i]);

	return 0;
}