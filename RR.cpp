#include "src/header.h"

bool RRcompareArrivalTime(const Process &p1, const Process &p2)
{
    return p1.arrival_time < p2.arrival_time;
}
// baiza
void RR1_Scheduler(deque<Process> processes, int numCores, int quantum)
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
        cout << currentTime << " ";
        for (int i = 0; i < numCores; i++)
        {
            // cout << cores[i].process_id << endl;
            if (cores[i].process_id == -1 && !readyQueue.empty())
            {
                if ((readyQueue.front().arrival_time + readyQueue.front().IO_start_time) == currentTime)
                {
                    IOQueue.push(readyQueue.front());
                    // cout << "Process " << readyQueue.front().process_id << " is now in IO Queue" << endl;
                    readyQueue.pop();
                }
                else
                {
                    // cout << "lol" << endl;
                    cores[i] = readyQueue.front();
                    readyQueue.pop();
                }
            }
            cout << cores[i].process_id << " ";
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
            // cout << "Process " << IOQueue.front().process_id << " is now in ready Queue" << endl;
            IOQueue.pop();
        }
        // printTableRow(currentTime, cores);
        //   cout << quantum << endl;
        //   cout << readyQueue.size() << endl;
        currentTime += quantum;
        cout << endl;
        // if (currentTime == 10)
        // {
        //     break;
        // }
    }
}

void RR_Scheduler(deque<Process> processes, int numCores, int quantum)
{
    queue<Process> readyQueue;
    vector<Process> IOqueue;
    int completedProcesses = 0, processIdx = 0;
    vector<Process> cores(numCores, {-1, 0, 0, 0, 0, 0});
    sort(processes.begin(), processes.end(), RRcompareArrivalTime);
    printTableHeader(numCores);

    for (int currentTime = 0; completedProcesses < processes.size(); currentTime++)
    {
        // fill the cores
        for (int coreIdx = 0; coreIdx < numCores; coreIdx++)
        {
            if (cores[coreIdx].process_id == -1 && processIdx <= processes.size())
            {
                if (processes[processIdx].arrival_time <= currentTime)
                {
                    cores[coreIdx] = processes[processIdx];
                    processIdx++;
                }
            }
        }

        // Arrived processes
        while (processIdx < processes.size() and processes[processIdx].arrival_time <= currentTime)
        {
            readyQueue.push(processes[processIdx]);
            processIdx++;
        }
        // printTableRow(currentTime, cores);
        //    execute
        for (int cr = 0; cr < numCores; cr++)
        {
            if (cores[cr].IO_start_time + cores[cr].arrival_time == currentTime) // IO
            {
                IOqueue.push_back(cores[cr]);
                cores[cr].setToZero();
            }
            else if (cores[cr].process_id != -1) // execute
            {
                cores[cr].time_slice++;
                cores[cr].remaining_time--;
                if (cores[cr].remaining_time <= 0)
                {
                    completedProcesses++;
                    cores[cr].setToZero();
                }
                else if (cores[cr].time_slice % quantum == 0)
                {
                    readyQueue.push(cores[cr]);
                }
            }
            else // idle core from last cycle
            {
                cores[cr] = readyQueue.front();
                readyQueue.pop();
                if (cores[cr].IO_start_time + cores[cr].arrival_time <= currentTime) // IO
                {
                    IOqueue.push_back(cores[cr]);
                    cores[cr].setToZero();
                    continue;
                }
                cores[cr].time_slice++;
                cores[cr].remaining_time--;
                if (cores[cr].remaining_time <= 0)
                {
                    completedProcesses++;
                    cores[cr].setToZero();
                }
                else if (cores[cr].time_slice % quantum == 0)
                {
                    readyQueue.push(cores[cr]);
                }
            }
        }

        for (auto IO = IOqueue.begin(); IO != IOqueue.end();)
        {
            IO->IO_time--;
            if (IO->IO_time == 0)
            {
                readyQueue.push(*IO);
                IO = IOqueue.erase(IO);
            }
            ++IO;
        }

        // cout << completedProcesses << " | IDX: " << processIdx << " | rdy: " << readyQueue.size() << " | IO: " << IOqueue.size() << " " << endl;
    }
}
