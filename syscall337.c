#include <linux/linkage.h>
#include <linux/kernel.h>

asmlinkage void syscall337(int pid ,long start_time, long end_time){
	static const long base = 100000000;
	printk("[Project1] %d %ld.%09ld, %ld.%09ld\n", pid, start_time/base, start_time%base, end_time/base, end_time%base);
}
