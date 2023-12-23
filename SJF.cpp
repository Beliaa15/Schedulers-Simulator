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
    int maxTurnaround = 0;
    int totalTurnaround = 0;
    int totalResponse = 0;

    // cout << "Process Name\tTurnaround Time\tResponse Time\tGantt Chart\n";
    for (int i = 0; i < n; i++)
    {
        totalTurnaround += processes[i].turnAround_time;
        totalResponse += processes[i].response_time;

        if (processes[i].turnAround_time > maxTurnaround)
        {
            maxTurnaround = processes[i].turnAround_time;
        }

        // cout << processes[i].process_name << "\t\t" << processes[i].turnAround_time << "\t\t" << processes[i].response_time << "\t\t";

        for (int j = 0; j < processes[i].CPU_time; j++)
        {
            cout << processes[i].process_name;
        }
        cout << endl;
    }

    double averageTurnaround = static_cast<double>(totalTurnaround) / n;
    double averageResponse = static_cast<double>(totalResponse) / n;

    cout << "\nAverage Turnaround Time: " << averageTurnaround << endl;
    cout << "Average Response Time: " << averageResponse << endl;
    cout << "Maximum Turnaround Time: " << maxTurnaround << endl;
    cout << endl;
}

void SJF_Scheduler(deque<Process> processes, int numCores)
{
    sort(processes.begin(), processes.end(), compareArrival);

    int currentTime = 0;
    int completedProcesses = 0;
    deque<Process> readyQueue;

    while (completedProcesses < processes.size())
    {
        // Move processes to ready queue when they arrive
        while (!processes.empty() && processes.front().arrival_time <= currentTime)
        {
            readyQueue.push_back(processes.front());
            processes.pop_front();
        }

        // Sort ready queue by execution time
        sort(readyQueue.begin(), readyQueue.end(), compareExecutionTime);

        // Simulate CPU execution
        for (int i = 0; i < min(numCores, int(readyQueue.size())); i++)
        {
            if (!readyQueue.empty())
            {
                Process &currentProcess = readyQueue.front();

                // Update turnaround and response times
                currentProcess.turnAround_time = currentTime + currentProcess.CPU_time - currentProcess.arrival_time;
                currentProcess.response_time = currentTime - currentProcess.arrival_time;

                // Update current time
                currentTime++;

                // Print Gantt chart for CPU execution time
                for (int j = 0; j < currentProcess.CPU_time; j++)
                {
                    cout << currentProcess.process_name;
                }

                // Remove the completed process from the ready queue
                readyQueue.pop_front();
                completedProcesses++;
            }
        }
    }

    SJF_printResults(processes, processes.size());
}
