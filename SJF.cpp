#include "src/header.h"

int total_time = 0;

bool compareArrivalTime(Process &a, Process &b)
{
    if (a.arrival_time == b.arrival_time)
    {
        return a.burst_time < b.burst_time;
    }
    else
    {
        return a.arrival_time < b.arrival_time;
    }
}

void printGanttChart(vector<Process> processes)
{
    vector<char> timeline(total_time, 'i');

    int current_time = 0;
    for (auto &p : processes)
    {
        for (int i = 0; i < p.burst_time; ++i)
        {
            timeline[current_time] = p.process_id;
            ++current_time;
        }
    }

    for (int i = 0; i < total_time; ++i)
        cout << i << " ";
    cout << endl;

    for (auto &c : timeline)
    {
        cout << c << " ";
    }
    cout << endl;
}

void SJF_Scheduler(vector<Process> processes, int n)
{
    sort(processes.begin(), processes.end(), compareArrivalTime);
    for (auto d : processes)
    {
        total_time += d.burst_time;
        for (int i = 0; i < d.burst_time; ++i)
        {
            cout << d.process_id << " ";
        }
    }

    cout << "\n\nGantt chart representation:\n";
    printGanttChart(processes);
}
