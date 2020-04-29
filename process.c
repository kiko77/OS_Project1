#define _GNU_SOURCE
#include "process.h"
#include <sys/types.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void assign_CPU(int pid, int cpu){
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(cpu, &mask);

	if(sched_setaffinity((pid_t)pid, sizeof(mask), &mask)<0){perror("sched_setaffinity");}
}
int proc_execu(Process proc){		
	int pid = fork();

	//assign_CPU(pid, 1);//CPU1	
	if(pid==0){
		long start_time = syscall(335);//gettime
		for(int i=0; i<proc.execu_time; i++){
			volatile unsigned long j;
			for(j=0; j<1000000UL; j++);
		}
		long end_time = syscall(335);
		syscall(337, getpid(), start_time, end_time);//printk
		exit(0);		 
	}
	else if(pid < 0){printf("process:error!!!");}
	
	assign_CPU(pid, 1);
	return pid;
}
void proc_wake(int pid){
	struct sched_param param;
	param.sched_priority = 0;
	if(sched_setscheduler((pid_t)pid, SCHED_OTHER, &param) < 0){perror("sched_setscheduler");} 
}

void proc_block(int pid){
	struct sched_param param;
	param.sched_priority = 0;
	if(sched_setscheduler((pid_t)pid, SCHED_IDLE, &param) < 0){perror("sched_setscheduler");} 
}

