
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
    int priority;
    char pro_specifier[MAX_LINE_LENGTH];
    int end_time;
    int time_slice;
    bool completed;
    bool holder;

    void setToZero()
    {
        process_id = -1;
        arrival_time = 0;
        CPU_time = 0;
        execution_time = 0;
        remaining_time = 0;
        burst_time = 0;
        remaining_time = 0;
        IO_start_time = 0;
        IO_time = 0;
        first_runtime = 0;
        waiting_time = 0;
        turnAround_time = 0;
        response_time = 0;
        priority = 0;
    }
} Process;

double calculateResponseTime(deque<Process> processes, int scheduler);
double calculateTurnaroundTime(deque<Process> processes, int scheduler);
void choose_scheduler(deque<Process> processes, int numCores);
void getIntegerOnly(int *ptr);

void FCFS_Scheduler(deque<Process> processes, int numCores);
void SJF_Scheduler(deque<Process> processes, int numCores);
void STCF_Scheduler(deque<Process> processes, int num_cores);
void RR1_Scheduler(deque<Process> processes, int numCores, int quantum);
void RR_Scheduler(deque<Process> processes, int numCores, int quantum);
void Priority_Scheduler(deque<Process> processes, int numCores);
bool compareArrival(Process &a, Process &b);
void printTableHeader(int numCores);
void printTableRow(int currentTime, vector<Process> &cores);

// bool compareExecutionTime(Process &a, Process &b);

#endif