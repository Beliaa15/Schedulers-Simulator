#include "src/header.h"

bool PrioritycompareArrivalTime(const Process &p1, const Process &p2)
{
    if(p1.arrival_time != p2.arrival_time) {
        return p1.arrival_time < p2.arrival_time;
    }
    
    return p1.execution_time < p2.execution_time;
}

void Priority_Scheduler(deque<Process> processes, int numCores){
    queue<Process> readyQueue;
    vector<Process> IOQueue;
    int currentTime = 0, completedProcesses = 0, processIdx = 0;
    vector<Process> cores(numCores, {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    for(int i = 0; i < processes.size(); i++){
        processes[i].time_slice = 0;
    }
    sort(processes.begin(), processes.end(), PrioritycompareArrivalTime);
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

        // Arrived processes
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
                if(!readyQueue.empty()){
                    cores[cr] = readyQueue.front();
                    readyQueue.pop();
                }
            }
            if(cores[cr].process_id != -1){
                if(cores[cr].priority > readyQueue.front().priority){
                    readyQueue.push(cores[cr]);
                    cores[cr] = readyQueue.front();
                    readyQueue.pop();
                }
                else{
                    cores[cr].remaining_time--;
                    if(cores[cr].remaining_time <= 0){
                        completedProcesses++;
                        cores[cr].setToZero();
                        if(!readyQueue.empty()){
                            cores[cr] = readyQueue.front();
                            readyQueue.pop();
                        }
                    }
                }
            }
            else{
                if(!readyQueue.empty()){
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
    }
    printTableRow(currentTime, cores);
}