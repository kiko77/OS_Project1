#ifndef PRO
#define PRO

#include<sys/types.h>

typedef struct process{
	char name[32];
	int ready_time;
	int execu_time;
	pid_t pid;	
}Process;

void assign_CPU(int pid, int cpu);
int proc_execu(Process proc);
void proc_wake(int pid);
void proc_block(int pid);

#endif		
