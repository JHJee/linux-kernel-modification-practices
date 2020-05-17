#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>
void sys_mygetsid(int* x){
	*x = 2015113852;
	printk("sys_mygetsid() : %d\n", *x);
}
SYSCALL_DEFINE1(mygetsid, int*, x)
{
	sys_mygetsid(x);
}
