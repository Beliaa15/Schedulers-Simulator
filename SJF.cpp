#include "src/header.h"

bool compareArrival(Process &a, Process &b)
{
    return a.arrival_time < b.arrival_time;
}

bool compareExecutionTime(Process &a, Process &b)
{
    return a.CPU_time < b.CPU_time;
}

void SJF_printResults(deque<Process> processes, int n)
{
    int spaces = 0;
    printf("Process Name\tTurn around\tResponse time\tGantt chart\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s\t\t|", processes[i].process_name);
        printf("\t%d\t|", processes[i].turnAround_time);
        printf("\t%d\t|", processes[i].response_time);

        for (int j = 0; j < processes[i].CPU_time; j++)
        {
            if (i == 0)
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
            cout << processes[i].process_name;
        }
        printf("\n");
    }
    printf("\n\n");
}

void SJF_Scheduler(deque<Process> processes, int numCores)
{
    sort(processes.begin(), processes.end(), compareArrival);

    // simulate the 4 cores
    vector<int> cores(numCores, -1);

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < processes.size())
    {
        // Select processes that have arrived but not yet completed
        vector<Process> readyProcesses;
        for (Process &p : processes)
        {
            if (p.arrival_time <= currentTime)
            {
                readyProcesses.push_back(p);
            }
        }

        // If there are processes ready to be scheduled
        if (!readyProcesses.empty())
        {
            // Sort by remaining CPU time (SJF)
            sort(readyProcesses.begin(), readyProcesses.end(), compareExecutionTime);

            // Assign processes to cores
            for (int i = 0; i < min(numCores, (int)readyProcesses.size()); i++)
            {
                cores[i] = readyProcesses[i].process_id;
                readyProcesses[i].response_time = currentTime;
                readyProcesses[i].turnAround_time = currentTime + readyProcesses[i].CPU_time;
                completedProcesses++;
                currentTime++;
            }
        }
        else
        {
            // If no processes are ready, increment time
            currentTime++;
        }
    }

    double avrage_turn = calculateTurnaroundTime(processes, SJF);
    double avrage_res = calculateResponseTime(processes, SJF);

    SJF_printResults(processes, processes.size());

    printf("average of Turnaround time = %0.2f\n", avrage_turn);
    printf("average of Response time = %0.2f\n", avrage_res);
}
