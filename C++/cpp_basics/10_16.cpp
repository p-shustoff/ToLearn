#include <stdio.h>

template <class T>
T get_and_zero(T &b)
{
	T old_b(b);
	b = 0;
	return old_b;
}
