#include "src/header.h"

double calculateTurnaroundTime(vector<Process> processes, int n, int scheduler)
{
    double counter = 0, sum = 0;
    /*switch (scheduler)
    {
    case SJF:

    case FCFS:

    case RR:

    default:
        break;
    }*/
    return (sum / (counter + 1));
}

double calculateResponseTime(vector<Process> processes, int n, int scheduler)
{
    double counter = 0, sum = 0;
    /*switch (scheduler)
    {
    case SJF:

    case FCFS:

    case RR:

    default:
        break;
    }*/
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