#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include "process.h"
#include "queue.h"

#define FIFO 1
#define RR 2
#define SJF 3
#define PSJF 4


static int running_id;
static int time;
static int last_time;
static int finish_num;
struct Queue *queue;
int flag = 1;

int get_next(Process *proc, int proc_num, int policy){
	int id = -1;

	if(policy == FIFO){
		if(running_id != -1){return running_id;}
		if(proc[finish_num].pid != -1){id = finish_num;}
	}
	else if(policy == RR){	
		if(running_id == -1){
			id = pop(queue);
		}
		else if((time-last_time) % 500 == 0){
			push(queue, running_id);
			id = pop(queue);
		}
		else{id = running_id;}
	}
	else if(policy == SJF || policy == PSJF){
		if(policy == SJF && running_id != -1){return running_id;}	
		if(flag || running_id == -1){
			for(int i=0; i<proc_num; i++){
				if((proc[i].pid != -1 && proc[i].execu_time > 0) && (id == -1 || proc[i].execu_time < proc[id].execu_time)){
					id = i;
				}
			}

		}
		flag = 0;
	}
	return id;
}

int cmp(const void *a, const void *b){
	return  ((Process*)a)->ready_time - ((Process*)b)->ready_time;
}

void scheduler(int policy, int proc_num, Process *proc){
	qsort(proc, proc_num, sizeof(Process), cmp);
	//initial
	running_id = -1;
	time = 0;
	last_time = -1;
	finish_num = 0;

	//assign CPU0 to scheduler()
	assign_CPU(getpid(), 0);
	//give CPU1 the higherst priority
	proc_wake(getpid());

	queue = (struct Queue *)malloc(sizeof(struct Queue));
	queue->f = 0;
	queue->b = 0;


	while(1){
		/*check finish*/
		if (running_id != -1 && proc[running_id].execu_time==0){
			//fprintf(stderr, "%s finish at time %d.\n", proc[running_id].name, time);
			//wait proc[running_id]
			waitpid(proc[running_id].pid, NULL, 0);
			printf("%s %d\n", proc[running_id].name, proc[running_id].pid);
			running_id = -1;
			finish_num++;
			if(finish_num == proc_num){break;}
		}

		/*check ready*/
		for(int i=0; i<proc_num; i++){
			if(proc[i].ready_time == time){
				flag = 1;
				//give proc[i] pid
				proc[i].pid = proc_execu(proc[i]);
				//block proc[i]
				proc_block(proc[i].pid);
				if(policy == RR){push(queue, i);}
			}
		}

		/*check run*/
		//get the next_id
		int next_id = get_next(proc, proc_num, policy);
		if(next_id != -1 && running_id != next_id){
			//unblock proc[next_id]
			proc_wake(proc[next_id].pid);
			//block proc[running_id]
			proc_block(proc[running_id].pid);
			running_id = next_id;
			last_time = time;
		}	

		if(running_id != -1){proc[running_id].execu_time--;}
		//run unit time
		volatile unsigned long j;
		for(j=0; j<1000000UL; j++);
		time++;

	}
	return;		
}
