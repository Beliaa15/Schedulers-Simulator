#include "src/header.h"

bool RRcompareArrivalTime(const Process &p1, const Process &p2)
{
    return p1.arrival_time < p2.arrival_time;
}

void RR_Scheduler(deque<Process> processes, int numCores, int quantum)
{
    queue<Process> readyQueue;
    queue<Process> IOQueue;
    int currentTime = 0;
    int completedProcesses = 0;
    vector<Process> cores(numCores, {-1, 0, 0, 0, 0, 0});
    sort(processes.begin(), processes.end(), RRcompareArrivalTime);
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
        // cout << readyQueue.size() << endl;
        for (int i = 0; i < numCores; i++)
        {
            cout << cores[i].process_id << endl;
            if (cores[i].process_id == -1 && !readyQueue.empty())
            {
                if ((readyQueue.front().arrival_time + readyQueue.front().IO_start_time) == currentTime)
                {
                    IOQueue.push(readyQueue.front());
                    cout << "Process " << readyQueue.front().process_id << " is now in IO Queue" << endl;
                    readyQueue.pop();
                }
                else
                {
                    // cout << "lol" << endl;
                    cores[i] = readyQueue.front();
                    readyQueue.pop();
                }
            }
            cout << cores[i].process_id << endl;
            if (cores[i].process_id != -1)
            {
                cores[i].remaining_time -= quantum;
                cores[i].execution_time -= quantum;
                if (cores[i].remaining_time < 0)
                {
                    cores[i] = {-1, 0, 0, 0, 0, 0};
                    completedProcesses++;
                }
                else
                {
                    readyQueue.push(cores[i]);
                    cores[i] = {-1, 0, 0, 0, 0, 0};
                }
            }
        }
        IOQueue.front().IO_time--;
        if (IOQueue.front().IO_time == 0)
        {
            readyQueue.push(IOQueue.front());
            cout << "Process " << IOQueue.front().process_id << " is now in ready Queue" << endl;
            IOQueue.pop();
        }
        //printTableRow(currentTime, cores);
        // cout << quantum << endl;
        // cout << readyQueue.size() << endl;
        currentTime += quantum;
        // if (currentTime == 10)
        // {
        //     break;
        // }
    }
}