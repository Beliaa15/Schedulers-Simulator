#include "src/header.h"

bool compareCPUtime(Process &a, Process &b)
{
    // don't foreget to check for the late arrival time first
    return a.CPU_time > b.CPU_time;
}

void SJF_printResults(vector<Process> processes, int n)
{
    int spaces = 0;
    printf("Process Name\tTurn around\tResponse time\tGantt chart\n");
    for (int i = n - 1; i >= 0; i--)
    {
        printf("%s\t\t|", processes[i].process_name);
        printf("\t%d\t|", processes[i].turnAround_time);
        printf("\t%d\t|", processes[i].response_time);

        for (int j = 0; j < processes[i].CPU_time; j++)
        {
            if (i == n - 1)
            {
                spaces += processes[i].CPU_time;
                break;
            }
            else
            {
                for (int i = 0; i < spaces; i++)
                {
                    cout << " ";
                }
                spaces += processes[i].CPU_time;
                break;
            }
        }

        // Print Gantt chart for CPU execution time only
        for (int j = 0; j < processes[i].CPU_time; j++)
        {
            cout << processes[i].pro_specifier;
        }
        printf("\n");
    }
    printf("\n\n");
}

void SJF_Scheduler(vector<Process> processes, int n)
{
    sort(processes.begin(), processes.begin() + n, compareCPUtime);
    double avrage_turn = calculateTurnaroundTime(processes, n, SJF);
    double avrage_res = calculateResponseTime(processes, n, SJF);

    SJF_printResults(processes, n);

    printf("average of Turnaround time=%0.2f\n", avrage_turn);
    printf("average of Response time=%0.2f\n", avrage_res);
}
