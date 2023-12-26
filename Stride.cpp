#include "src/header.h"

bool StrideCompare(const Process& p1, const Process& p2) {
    if(p1.arrival_time != p2.arrival_time) {
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

void Stride_Scheduler(deque<Process> processes, int numCores){
    int currentTime = 0, completedProcesses = 0, processIdx = 0;
    vector<Process> cores(numCores, {-1, 0, 0, 0, 0, 0});
    vector<Process> IOQueue;
    queue<Process> readyQueue;
    for (Process &process : processes)
    {
        process.stride = 2000 / process.CPU_time;
        process.pass = 0;
    }
    sort(processes.begin(), processes.end(), StrideCompare);
    for (Process process : processes)
    {
        cout << process.process_id << " " << process.pass << " " << process.stride << " " << process.arrival_time <<  " " << process.CPU_time <<endl;
    }

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
            Process min;
            if(!readyQueue.empty()){
                min = getMinumum(readyQueue);
            }
            if ((cores[cr].IO_start_time + cores[cr].arrival_time) == currentTime) // IO
            {
                IOQueue.push_back(cores[cr]);
                cores[cr].setToZero();
                if (!readyQueue.empty())
                {
                    cores[cr] = readyQueue.front();
                    readyQueue.pop();
                }
            }
            else if (cores[cr].process_id != -1){
                cores[cr].remaining_time--;
                cores[cr].pass += cores[cr].stride;
                if (cores[cr].remaining_time <= 0)
                {
                    cores[cr].setToZero();
                    if(!readyQueue.empty()){
                        cores[cr] = readyQueue.front();
                        readyQueue.pop();
                    }
                    completedProcesses++;
                }
            else if (cores[cr].pass > min.pass && !readyQueue.empty())
                {
                    readyQueue.push(cores[cr]);
                    cores[cr] = min;
                    readyQueue.pop();
                }
            }
            else {
                if (!readyQueue.empty())
                {
                    cores[cr] = readyQueue.front();
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
        //printTableRow(currentTime, cores);
        // for (int i = 0; i < numCores; i++)
        // {
        //     cout << cores[i].process_id << " " << cores[i].pass << endl;
        // }
        
    }
    //printTableRow(currentTime, cores);
}