#include <unistd.h>

#define __NR_hello 436

int hello(int n, int m)
{
	return syscall(__NR_hello, n, m);
}
