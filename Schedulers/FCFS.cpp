#include "src/header.h"

bool FCFScompareArrivalTime(const Process &p1, const Process &p2)
{
    return p1.arrival_time < p2.arrival_time;
}

void FCFS_Scheduler(deque<Process> processes, int numCores)
{
    int currentTime = 0;
    int completedProcesses = 0;
    double totalTurnTime = 0;
    double totalResponseTime = 0;
    sort(processes.begin(), processes.end(), FCFScompareArrivalTime);
    vector<Process> cores(numCores, {-1, 0, 0, 0, 0, 0});
    queue<Process> readyQueue;
    printTableHeader(numCores);

    while (completedProcesses < processes.size())
    {
        for (Process process : processes)
        {
            if (process.arrival_time == currentTime)
            {
                readyQueue.push(process);
                process.first_runtime = currentTime;
                process.response_time = process.first_runtime - process.arrival_time;
                totalResponseTime += process.response_time;
            }
        }

        for (int i = 0; i < numCores; i++)
        {
            if (cores[i].process_id == -1 && !readyQueue.empty())
            {
                cores[i] = readyQueue.front();
                readyQueue.pop();
            }
            if (cores[i].process_id != -1)
            {
                cores[i].remaining_time--;
                if (cores[i].remaining_time < 0)
                {
                    for (auto process : processes)
                    {
                        if (process.process_id == cores[i].process_id)
                        {
                            process.end_time = currentTime;
                            process.turnAround_time = process.end_time - process.arrival_time;
                            totalTurnTime += process.turnAround_time;
                            break;
                        }
                    }
                    cores[i] = {-1, 0, 0, 0, 0, 0};
                    completedProcesses++;
                }
            }
        }
        printTableRow(currentTime, cores);
        currentTime++;
    }
    cout << "Average Turnaround Time: " << totalTurnTime / processes.size() << endl;
    cout << "Average Response Time: " << totalResponseTime / processes.size() << endl;
}