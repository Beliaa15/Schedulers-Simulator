#include "src/header.h"

bool compareRemainingTime(const Process &p1, const Process &p2)
{
    return p1.remaining_time > p2.remaining_time;
}

bool compareArrival(Process &a, Process &b)
{
    return a.arrival_time < b.arrival_time;
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
                if (cores[i].remaining_time < 0)
                {
                    cores[i].end_time = currentTime;
                    // cout << "\t\t\tCore " << i + 1 << " completed Process " << cores[i].process_id << " at time " << currentTime << endl;
                    cores[i] = {-1, 0, 0, 0, 0, 0};
                    completedProcesses++;
                }
            }
        }
        printTableRow(currentTime, cores);
        currentTime++;
    }
    printTableRow(currentTime, cores);
}