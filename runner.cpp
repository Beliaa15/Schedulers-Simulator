#include "src/header.h"

void choose_scheduler(deque<Process> processes, int numCores)
{
    int sch_choose;
    printf("-------------------------------------------------------\n");
    printf("\t\t\033[1;34mSelect Scheduler\033[0m\n1-First Come First Served\n2-Shortest Job First\n3-Shortest To Complete First\n4-Multi-Level Feedback Queue \n5-Round Robin\n6-Stride\n7-Priority\n");
    getIntegerOnly(&sch_choose);
    switch (sch_choose)
    {
    case 1:
        FCFS_Scheduler(processes, 4);
        break;
    case 2:
        SJF_Scheduler(processes, 4);
        break;
    case 3:
        STCF_Scheduler(processes, 4);
        break;
    case 4:
        // MLFQ_Scheduler(processes, 4);
        break;
    case 5:
        RR_Scheduler(processes, 4, 2);
        break;
    case 6:
        // Stride_Scheduler();
        break;
    case 7:
        // Priority_Scheduler();
        break;
    default:
        printf("Invalid number!.\n");
        break;
    }
}

int main()
{
    int Dataset_processes_num = 0, user_processes_num = 0, choose;
    char c;
    system("clear");
    FILE *fp = fopen("input2.txt", "r");

    if (fp == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    // Read the first line and discard it
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, fp);
    fgets(line, MAX_LINE_LENGTH, fp);

    // Create an array of Process structs to hold the data
    deque<Process> processes;

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        Process temp;
        sscanf(line, "%d | %s | %d | %d | %d | %d | %s", &temp.process_id, temp.process_name, &temp.arrival_time, &temp.CPU_time, &temp.IO_time, &temp.IO_start_time, temp.pro_specifier);
        temp.execution_time = temp.CPU_time - temp.IO_time;
        temp.remaining_time = temp.CPU_time;
        processes.push_back(temp);
        Dataset_processes_num++;
    }

    fclose(fp);
    int i = 0;

    // main window
    while (true)
    {
        printf("\t\t\033[1;32mOur Humble Simulation\033[0m\nEnter:\t 1-Create a new process \n\t 2-Start simulation with current dataset\n");
        getIntegerOnly(&choose);

        if (choose == 1)
        {
            printf("-------------------------------------------------------\n");
            printf("Enter the number of processes:");
            getIntegerOnly(&user_processes_num);
            while (user_processes_num--)
            {
                Process temp;
                temp.process_id = Dataset_processes_num + i + 1;
                strcpy(temp.process_status, "ready");

                printf("Enter process %d Name: ", i + 1);
                cin >> temp.process_name;

                printf("Enter process %d arrival time: ", i + 1);
                getIntegerOnly(&temp.arrival_time);

                printf("Enter process %d CPU time: ", i + 1);
                getIntegerOnly(&temp.CPU_time);

                printf("Enter process %d IO time: ", i + 1);
                getIntegerOnly(&temp.IO_time);

                if (temp.IO_time != 0)
                {
                    printf("Enter process %d IO start time: ", i + 1);
                    getIntegerOnly(&temp.IO_start_time);
                }

                printf("Enter process %d specifier: ", i + 1);
                cin >> temp.pro_specifier;

                temp.execution_time = temp.CPU_time - temp.IO_time;
                temp.remaining_time = temp.CPU_time;

                i++;
                processes.push_back(temp);
            }

            choose_scheduler(processes, 4);
        }
        else if (choose == 2)
        {
            choose_scheduler(processes, 4);
        }
        else
        {
            printf("Invalid number!.\n Please enter a valid number.\n");
        }
    }

    return 0;
}