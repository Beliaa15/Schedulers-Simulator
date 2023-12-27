#include "src/header.h"

void getIntegerOnly(int *ptr)
{
    char *p, s[100];
    while (fgets(s, sizeof(s), stdin))
    {
        *ptr = strtol(s, &p, 10);
        if (p == s || *p != '\n')
        {
            printf("\033[1;31m(Integers Only) \033[0m");
        }
        else
            break;
    }
}

void printTableHeader(int numCores)
{
    cout << setw(10) << "Time";
    for (int i = 1; i <= numCores; ++i)
    {
        cout << setw(15) << "Core " << i;
    }
    cout << endl;
}

void printTableRow(int currentTime, vector<Process> &cores)
{
    cout << setw(10) << currentTime;
    for (const Process &core : cores)
    {
        if (core.process_id != -1)
        {
            cout << setw(15) << "P" << core.process_id;
        }
        else
        {
            cout << setw(15) << "Idle";
        }
    }
    cout << endl;
    sleep(1);
}