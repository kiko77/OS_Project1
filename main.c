#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <sys/types.h>
#include "process.h"

#define FIFO 1
#define RR 2
#define SJF 3
#define PSJF 4


void scheduler(int policy, int proc_num, Process *proc);

int main(){
	char policy[10];
	int proc_num;
	scanf("%s", policy);
	scanf("%d", &proc_num);
//	printf("%s %d\n", policy, proc_num);//////
	Process *proc = malloc(proc_num * sizeof(Process));
	for(int i=0; i<proc_num; i++){
		scanf("%s%d%d", proc[i].name, &proc[i].ready_time, &proc[i].execu_time);
		//printf("%s %d %d\n", proc[i].name, proc[i].ready_time, proc[i].execu_time);//////
		proc[i].pid=-1;
	}
	
	if(strcmp(policy, "FIFO")==0){
		scheduler(FIFO, proc_num, proc);
	}
	else if(strcmp(policy, "RR")==0){
		scheduler(RR, proc_num, proc);
	}			
	else if(strcmp(policy, "SJF")==0){
		scheduler(SJF, proc_num, proc);
	}	
	else if(strcmp(policy, "PSJF")==0){
		scheduler(PSJF, proc_num, proc);
	}
}		
