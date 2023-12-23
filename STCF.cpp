#include "src/header.h"
bool compareRemainingTime(const Process &p1, const Process &p2)
{
    return p1.remaining_time > p2.remaining_time;
}

void printTableHeader(int numCores)
{
    cout << setw(10) << "Time";
    for (int i = 1; i <= numCores; ++i)
    {
        cout << setw(15) << "Core " << i;
    }
    cout << endl;
}

void printTableRow(int currentTime, vector<Process> &cores)
{
    cout << setw(10) << currentTime;
    for (const Process &core : cores)
    {
        if (core.process_id != -1)
        {
            cout << setw(11) << "P" << core.process_id << "(" << core.remaining_time << ")";
        }
        else
        {
            cout << setw(15) << "Idle";
        }
    }
    cout << endl;
}

void STCF_Scheduler(deque<Process> processes, int numCores)
{
    int currentTime = 0;
    int completedProcesses = 0;
    sort(processes.begin(), processes.end(), compareArrival);
    priority_queue<Process, vector<Process>, decltype(&compareRemainingTime)> readyQueue(&compareRemainingTime);
    vector<Process> cores(numCores, {-1, 0, 0, 0, 0, 0});

    printTableHeader(numCores);

    while (completedProcesses < processes.size())
    {
        for (Process process : processes)
        {
            if (process.arrival_time == currentTime)
            {
                readyQueue.push(process);
            }
        }

        printTableRow(currentTime, cores);

        for (int i = 0; i < numCores; i++)
        {
            if (cores[i].process_id == -1 && !readyQueue.empty())
            {
                cores[i] = readyQueue.top();
                readyQueue.pop();
            }
            else if (!readyQueue.empty() && cores[i].remaining_time > readyQueue.top().remaining_time)
            {
                readyQueue.push(cores[i]);
                cores[i] = readyQueue.top();
                readyQueue.pop();
            }
            if (cores[i].process_id != -1)
            {
                cores[i].remaining_time--;
                if (cores[i].remaining_time == 0)
                {
                    cores[i].end_time = currentTime;
                    // cout << "\t\t\tCore " << i + 1 << " completed Process " << cores[i].process_id << " at time " << currentTime << endl;
                    cores[i] = {-1, 0, 0, 0, 0, 0};
                    completedProcesses++;
                }
            }
        }
        currentTime++;
    }
    printTableRow(currentTime, cores);
}