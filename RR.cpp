#include "src/header.h"

bool RRcompareArrivalTime(const Process &p1, const Process &p2)
{
    return p1.arrival_time < p2.arrival_time;
}

void RR_Scheduler(deque<Process> processes, int numCores, int quantum)
{
    queue<Process> readyQueue, IOQueue;
    int currentTime = 0;
    int completedProcesses = 0;
    vector<Process> cores(numCores, {-1, 0, 0, 0, 0, 0});
    sort(processes.begin(), processes.end(), RRcompareArrivalTime);
    while(completedProcesses < processes.size()){
        while (!IOQueue.empty())
        {
            Process& process = IOQueue.front();
            process.IO_time--;
            if (process.IO_time == 0)
            {
                IOQueue.pop();
                readyQueue.push(process);
            }
            else{
                IOQueue.pop();
                IOQueue.push(process);
            }
        }
        
    }
}