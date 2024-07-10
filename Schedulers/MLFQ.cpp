#include "src/header.h"

bool MLFQcompareArrivalTime(const Process &p1, const Process &p2)
{
    return p1.arrival_time < p2.arrival_time;
}

void MLFQ_Scheduler(deque<Process> processes, int numCores)
{
    vector<queue<Process>> readyQueues(5); // Assuming 5 priority levels
    vector<Process> IOqueue;
    int completedProcesses = 0, processIdx = 0;
    vector<Process> cores(numCores, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    sort(processes.begin(), processes.end(), MLFQcompareArrivalTime);

    for (int i = 0; i < processes.size(); i++)
    {
        processes[i].time_slice = 0;
        processes[i].remaining_time = processes[i].CPU_time;
    }
    // cout << processes.size() << endl;
    printTableHeader(numCores);

    for (int currentTime = 0; completedProcesses < processes.size(); currentTime++)
    {
        // fill the queues
        while (processIdx < processes.size() && processes[processIdx].arrival_time <= currentTime)
        {
            processes[processIdx].crnt_queue = 0;
            readyQueues[0].push(processes[processIdx]);
            processIdx++;
        }

        // execute
        for (int i = 0; i < numCores; i++)
        {
            if (cores[i].process_id == -1)
            {
                for (int j = 0; j < 5; j++)
                    if (!readyQueues[j].empty())
                    {
                        cores[i] = readyQueues[j].front();
                        readyQueues[j].pop();
                        break;
                    }
            }
            if (cores[i].process_id != -1)
            {
                cores[i].time_slice++;
                cores[i].remaining_time--;
                if (cores[i].remaining_time < 0)
                {
                    completedProcesses++;
                    cores[i].setToZero();
                    for (int j = 0; j < 5; j++)
                    {
                        if (!readyQueues[j].empty())
                        {
                            cores[i] = readyQueues[j].front();
                            cores[i].crnt_queue = j;
                            readyQueues[j].pop();
                            break;
                        }
                    }
                }
                else if (cores[i].time_slice % (2 << (cores[i].crnt_queue + 1)) == 0)
                {
                    // Demote process to a lower priority queue
                    if (cores[i].crnt_queue < 4)
                        cores[i].crnt_queue++;
                    cores[i].time_slice = 0;
                    readyQueues[cores[i].crnt_queue].push(cores[i]);
                    cores[i].setToZero();
                    for (int j = 0; j < 5; j++)
                    {
                        if (!readyQueues[j].empty())
                        {
                            cores[i] = readyQueues[j].front();
                            cores[i].crnt_queue = j;
                            readyQueues[j].pop();
                            break;
                        }
                    }
                }
            }
        }
        printTableRow(currentTime, cores);
    }
}