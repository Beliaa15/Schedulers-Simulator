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
                for (int j = 0; j < processes.size(); j++)
                {
                    if (processes[j].process_id == cores[i].process_id && !processes[j].holder)
                    {
                        processes[j].holder = true;
                        processes[j].first_runtime = currentTime;
                        processes[j].response_time = processes[j].first_runtime - processes[j].arrival_time;
                        break;
                    }
                }
            }
            else if (!readyQueue.empty() && cores[i].remaining_time > readyQueue.top().remaining_time)
            {
                readyQueue.push(cores[i]);
                cores[i] = readyQueue.top();
                readyQueue.pop();
                for (int j = 0; j < processes.size(); j++)
                {
                    if (processes[j].process_id == cores[i].process_id && !processes[j].holder)
                    {
                        processes[j].holder = true;
                        processes[j].first_runtime = currentTime;
                        processes[j].response_time = processes[j].first_runtime - processes[j].arrival_time;
                        break;
                    }
                }
            }
            if (cores[i].process_id != -1)
            {
                cores[i].remaining_time--;
                if (cores[i].remaining_time < 0)
                {
                    for (int j = 0; j < processes.size(); j++)
                    {
                        if (processes[j].process_id == cores[i].process_id)
                        {
                            processes[j].end_time = currentTime;
                        }
                    }
                    cores[i].setToZero();
                    completedProcesses++;
                }
            }
        }
        printTableRow(currentTime, cores);
        currentTime++;
    }
    printTableRow(currentTime, cores);

    double totalTurnTime = 0.0;
    double totalResponseTime = 0.0;
    for (int i = 0; i < processes.size(); i++)
    {
        processes[i].turnAround_time = processes[i].end_time - processes[i].arrival_time;
        totalTurnTime += processes[i].turnAround_time;
        totalResponseTime += processes[i].response_time;
    }
    cout << "Average Turnaround Time: " << totalTurnTime / (double)processes.size() << endl;
    cout << "Average Response Time: " << totalResponseTime / (double)processes.size() << endl;
}