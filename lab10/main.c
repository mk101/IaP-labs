#include <stdio.h>

typedef unsigned long ulong;

ulong fib(ulong n) {
	if (n == 1) return 0;
	else if (n == 2) return 1;
	else return fib(n-1) + fib(n-2);
} 

int main() {
	int m;
	ulong res = 0;
	printf("Input m: ");
	scanf("%d", &m);

	res = fib(m);

	printf("fib(%d) = %ld\n", m, res);
	
	return 0;
}

