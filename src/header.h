
#ifndef HEADER_H_

#include <bits/stdc++.h>
using namespace std;

#define MAX_SIZE 100
#define MAX_LINE_LENGTH 100
#define REALLY_BIG_NUM 400
#define MAX_PROCESSES 10
#define MAX_LEVELS 3
#define QUANTUM 2

#define SJF 1
#define FCFS 2
#define SRTCF 3
#define MLFQ 4
#define RR 5

extern int num_processes;

typedef struct
{
    int process_id;
    char process_name[MAX_LINE_LENGTH];
    int arrival_time;
    int CPU_time;
    int execution_time;
    int remaining_time;
    int burst_time;
    int io_time;
    int io_completion_time;
    int IO_time;
    int IO_start_time;
    char process_status[MAX_LINE_LENGTH];
    int first_runtime;
    int waiting_time;
    int turnAround_time;
    int response_time;
    char pro_specifier[MAX_LINE_LENGTH];
    int end_time;
    int time_slice;
    int turnaround_time;
    bool completed;
    bool holder;
} Process;

double calculateResponseTime(deque<Process> processes, int scheduler);
double calculateTurnaroundTime(deque<Process> processes, int scheduler);
void choose_scheduler(deque<Process> processes, int numCores);
void getIntegerOnly(int *ptr);

void SJF_Scheduler(deque<Process> processes, int numCores);
void SJF_printResults(deque<Process> processes, int n);
bool compareArrival(Process &a, Process &b);
bool compareExecutionTime(Process &a, Process &b);

void STCF_Scheduler(deque<Process> processes, int num_cores);

#endif