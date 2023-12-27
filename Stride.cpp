#include "src/header.h"

bool StrideCompare(const Process &p1, const Process &p2)
{
    if (p1.arrival_time != p2.arrival_time)
    {
        return p1.arrival_time < p2.arrival_time;
    }

    return p1.pass < p2.pass;
}

Process getMinumum(queue<Process> processes)
{
    Process min = processes.front();
    processes.pop();
    while (!processes.empty())
    {
        if (processes.front().pass < min.pass)
        {
            min = processes.front();
        }
        processes.pop();
    }
    return min;
}

void Stride_Scheduler(deque<Process> processes, int numCores)
{
    int currentTime = 0, completedProcesses = 0, processIdx = 0;
    vector<Process> cores(numCores, {-1, 0, 0, 0, 0, 0});
    vector<Process> IOQueue;
    queue<Process> readyQueue;
    for (Process &process : processes)
    {
        process.stride = 2000 / process.CPU_time;
        process.pass = 0;
        process.holder = false;
    }
    sort(processes.begin(), processes.end(), StrideCompare);

    printTableHeader(numCores);

    for (currentTime = 0; completedProcesses < processes.size(); currentTime++)
    {
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
        while (processIdx < processes.size() && processes[processIdx].arrival_time <= currentTime)
        {
            readyQueue.push(processes[processIdx]);
            processIdx++;
        }
        printTableRow(currentTime, cores);
        for (int cr = 0; cr < numCores; cr++)
        {
            if ((cores[cr].IO_start_time + cores[cr].arrival_time) == currentTime) // IO
            {
                IOQueue.push_back(cores[cr]);
                cores[cr].setToZero();
                if (!readyQueue.empty())
                {
                    cores[cr] = readyQueue.front();
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
                    readyQueue.pop();
                }
            }
            else if (cores[cr].process_id != -1)
            {
                cores[cr].remaining_time--;
                cores[cr].pass += cores[cr].stride;
                if (cores[cr].remaining_time <= 0)
                {
                    for (int i = 0; i < processes.size(); i++)
                    {
                        if (processes[i].process_id == cores[cr].process_id)
                        {
                            processes[i].end_time = currentTime;
                        }
                    }
                    cores[cr].setToZero();
                    if (!readyQueue.empty())
                    {
                        cores[cr] = readyQueue.front();
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
                        readyQueue.pop();
                    }
                    completedProcesses++;
                }
                else if (cores[cr].pass > readyQueue.front().pass && !readyQueue.empty())
                {
                    readyQueue.push(cores[cr]);
                    cores[cr] = readyQueue.front();
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
                    readyQueue.pop();
                }
            }
            else
            {
                if (!readyQueue.empty())
                {
                    cores[cr] = readyQueue.front();
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
                    readyQueue.pop();
                }
            }
        }
        for (int i = 0; i < IOQueue.size(); i++)
        {
            IOQueue[i].IO_time--;
            if (IOQueue[i].IO_time == 0)
            {
                readyQueue.push(IOQueue[i]);
                IOQueue.erase(IOQueue.begin() + i);
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
