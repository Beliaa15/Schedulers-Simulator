#include "src/header.h"

bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrival_time < p2.arrival_time;
}

bool compareRemainingTime(const Process& p1, const Process& p2) {
    return p1.remaining_time > p2.remaining_time;
}

void SJF_printResults(deque<Process> processes, int n)
{
    int maxTurnaround = 0;
    int totalTurnaround = 0;
    int totalResponse = 0;

    // cout << "Process Name\tTurnaround Time\tResponse Time\tGantt Chart\n";
    for (int i = 0; i < n; i++)
    {
        totalTurnaround += processes[i].turnAround_time;
        totalResponse += processes[i].response_time;

        if (processes[i].turnAround_time > maxTurnaround)
        {
            maxTurnaround = processes[i].turnAround_time;
        }

        // cout << processes[i].process_name << "\t\t" << processes[i].turnAround_time << "\t\t" << processes[i].response_time << "\t\t";

        for (int j = 0; j < processes[i].CPU_time; j++)
        {
            cout << processes[i].process_name;
        }
        cout << endl;
    }

    double averageTurnaround = static_cast<double>(totalTurnaround) / n;
    double averageResponse = static_cast<double>(totalResponse) / n;

    cout << "\nAverage Turnaround Time: " << averageTurnaround << endl;
    cout << "Average Response Time: " << averageResponse << endl;
    cout << "Maximum Turnaround Time: " << maxTurnaround << endl;
    cout << endl;
}

void SJF_Scheduler(deque<Process> processes, int num_cores)
{
    int currentTime = 0;
    int completedProcesses = 0;
    sort(processes.begin(), processes.end(), compareArrivalTime);
    priority_queue<Process, vector<Process>, decltype(&compareRemainingTime)> readyQueue(&compareRemainingTime);
    vector<Process> cores(num_cores, {-1, 0, 0, 0, 0, 0});
    while (completedProcesses < processes.size())
    {
        for (Process process :  processes)
        {
            if (process.arrival_time == currentTime)
            {
                readyQueue.push(process);
            }
        }
        for (int i = 0; i < num_cores; i++)
        {
            if (cores[i].process_id == -1 && !readyQueue.empty()){
                cores[i] = readyQueue.top();
                readyQueue.pop();
            }
            else if (!readyQueue.empty() && cores[i].remaining_time > readyQueue.top().remaining_time)
            {
                readyQueue.push(cores[i]);
                cores[i] = readyQueue.top();
                readyQueue.pop();
            }
            if(cores[i].process_id != -1){
                cores[i].remaining_time--;
                if (cores[i].remaining_time == 0){
                    cores[i].end_time = currentTime;
                    cout << "Core " << i + 1 << " completed Process " << cores[i].process_id << " at time " << currentTime << endl;
                    cores[i] = {-1, 0, 0, 0, 0, 0};
                    completedProcesses++;
                }
            }
            if(cores[i].process_id != -1){
                cout << "Core " << i + 1 << " running Process " << cores[i].process_id << " at time " << currentTime << endl;
            }
            else{
                cout << "Core " << i + 1 << " is idle at time " << currentTime << endl;
            }
        }
        currentTime++;
    }
    SJF_printResults(processes, processes.size());
}
