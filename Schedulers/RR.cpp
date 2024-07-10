#include "src/header.h"

bool RRcompareArrivalTime(const Process &p1, const Process &p2)
{
    return p1.arrival_time < p2.arrival_time;
}

void RR_Scheduler(deque<Process> processes, int numCores, int quantum)
{
    queue<Process> readyQueue;
    vector<Process> IOqueue;
    int completedProcesses = 0, processIdx = 0;
    vector<Process> cores(numCores, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    sort(processes.begin(), processes.end(), RRcompareArrivalTime);
    for (int i = 0; i < processes.size(); i++)
    {
        processes[i].time_slice = 0;
    }
    printTableHeader(numCores);
    int currentTime = 0;
    for (currentTime = 0; completedProcesses < processes.size(); currentTime++)
    {
        // fill the cores
        for (int coreIdx = 0; coreIdx < numCores; coreIdx++)
        {
            if (cores[coreIdx].process_id == -1 && processIdx < processes.size())
            {
                if (processes[processIdx].arrival_time <= currentTime)
                {
                    cores[coreIdx] = processes[processIdx];
                    processes[processIdx].first_runtime = currentTime;
                    processes[processIdx].response_time = processes[processIdx].first_runtime - processes[processIdx].arrival_time;
                    processes[processIdx].holder = true;
                    processIdx++;
                }
            }
        }

        // Arrived processes
        while (processIdx < processes.size() && processes[processIdx].arrival_time <= currentTime)
        {
            readyQueue.push(processes[processIdx]);
            processIdx++;
        }

        //    execute
        for (int cr = 0; cr < numCores; cr++)
        {
            if ((cores[cr].IO_start_time + cores[cr].arrival_time) == currentTime) // IO
            {
                IOqueue.push_back(cores[cr]);
                cores[cr].setToZero();
                if (!readyQueue.empty())
                {
                    cores[cr] = readyQueue.front();
                    readyQueue.pop();
                    for (int i = 0; i < processes.size(); i++)
                    {
                        if (processes[i].process_id == cores[cr].process_id && !processes[i].holder)
                        {
                            processes[i].holder = true;
                            processes[i].first_runtime = currentTime;
                            processes[i].response_time = processes[i].first_runtime - processes[i].arrival_time;
                            break;
                        }
                    }
                }
            }
            else if (cores[cr].process_id != -1) // execute
            {
                cores[cr].time_slice++;
                cores[cr].remaining_time--;
                if (cores[cr].remaining_time <= 0)
                {
                    completedProcesses++;
                    for (int i = 0; i < processes.size(); i++)
                    {
                        if (processes[i].process_id == cores[cr].process_id)
                        {
                            processes[i].end_time = currentTime;
                        }
                    }
                    cores[cr].setToZero();
                }
                else if (cores[cr].time_slice % quantum == 0)
                {
                    readyQueue.push(cores[cr]);
                    cores[cr] = readyQueue.front();
                    readyQueue.pop();
                    for (int i = 0; i < processes.size(); i++)
                    {
                        if (processes[i].process_id == cores[cr].process_id && !processes[i].holder)
                        {
                            processes[i].holder = true;
                            processes[i].first_runtime = currentTime;
                            processes[i].response_time = processes[i].first_runtime - processes[i].arrival_time;
                            break;
                        }
                    }
                }
            }
            else // idle core from last cycle
            {
                if (!readyQueue.empty())
                {
                    cores[cr] = readyQueue.front();
                    readyQueue.pop();
                    for (int i = 0; i < processes.size(); i++)
                    {
                        if (processes[i].process_id == cores[cr].process_id && !processes[i].holder)
                        {
                            processes[i].holder = true;
                            processes[i].first_runtime = currentTime;
                            processes[i].response_time = processes[i].first_runtime - processes[i].arrival_time;
                            break;
                        }
                    }
                }
            }
        }
        printTableRow(currentTime, cores);
        for (int i = 0; i < IOqueue.size(); i++)
        {
            IOqueue[i].IO_time--;
            if (IOqueue[i].IO_time == 0)
            {
                readyQueue.push(IOqueue[i]);
                IOqueue.erase(IOqueue.begin() + i);
                i--;
            }
        }
    }
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
