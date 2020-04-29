#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/timer.h>

asmlinkage long syscall335(void){
	static const long base = 1000000000;
	struct timespec t;
	getnstimeofday(&t);
	return t.tv_sec * base + t.tv_nsec;
}
