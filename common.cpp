#include "src/header.h"

double calculateTurnaroundTime(deque<Process> processes, int scheduler)
{
    double counter = 0, sum = 0;
    switch (scheduler)
    {
    case SJF:
        counter = 0;
        processes[0].waiting_time = 0;
        processes[0].turnAround_time = processes[0].execution_time;
        sum = processes[0].turnAround_time;
        for (int i = 1; i < processes.size(); i++)
        {
            processes[i].waiting_time = processes[i - 1].execution_time + processes[i - 1].waiting_time;
            processes[i].turnAround_time = processes[i].waiting_time + processes[i].execution_time;
            counter++;
            sum += processes[i].turnAround_time;
        }

    case FCFS:

    case RR:

    default:
        break;
    }
    return (sum / (counter + 1));
}

double calculateResponseTime(deque<Process> processes, int scheduler)
{
    double counter = 0, sum = 0;
    switch (scheduler)
    {
    case SJF:
        counter = 0;

        processes[0].response_time = processes[0].waiting_time;
        sum = processes[0].response_time;
        for (int i = 1; i < processes.size(); i++)
        {
            processes[i].response_time = processes[i].waiting_time;
            counter++;
            sum += processes[i].response_time;
        }
        break;
    case FCFS:

    case RR:

    default:
        break;
    }
    return (sum / (counter + 1));
}

void getIntegerOnly(int *ptr)
{
    char *p, s[100];
    while (fgets(s, sizeof(s), stdin))
    {
        *ptr = strtol(s, &p, 10);
        if (p == s || *p != '\n')
        {
            printf("\033[1;31m(Integers Only) \033[0m");
        }
        else
            break;
    }
}