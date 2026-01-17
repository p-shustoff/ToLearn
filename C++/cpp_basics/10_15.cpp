#include <stdio.h>

template <class T>
void swap3(T &x, T &y, T &z)
{
	T t;
	t = x;
	x = y;
	y = z;
	z = t; 
}

int main() {
	// 1. Testing tempalte for integers:
	int a = 10, b = 20, c = 30;
	printf("Integers before swapping: a = %d, b = %d, c = %d\n", a, b, c);
	swap3(a, b, c);
	printf("Integers after swapping: a = %d, b = %d, c = %d\n", a, b, c);
	// 2. Testing template on floats:
	float d = 10.543, e = 20.348, f = 30.764;
	printf("Floats before swapping: d = %lf, e = %lf, f = %lf\n", d, e, f);
	swap3(d, e, f);
	printf("Floats after swapping: d = %lf, e= %lf, f = %lf\n", d, e, f);
	// 3. Testing template on chars:
	char g = 'g', h = 'h', j = 'j';
	printf("Chars before swapping: g = %c, h = %c, j = %c\n", g, h, j);
	swap3(g, h, j);
	printf("Chars after swapping: g = %c, h = %c, j = %c\n", g, h, j);
	return 0;
}
