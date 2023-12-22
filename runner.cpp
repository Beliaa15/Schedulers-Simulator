#include "src/header.h"

void choose_scheduler(vector<Process> processes, int n)
{
    int sch_choose;
    printf("-------------------------------------------------------\n");
    printf("\t\t\033[1;34mSelect Scheduler\033[0m\n1-First Come First Served\n2-Shortest Job First\n3-Shortest Remaining Time First\n4-Multi-Level Feedback Queue \n5-Round Robin\n");
    getIntegerOnly(&sch_choose);
    switch (sch_choose)
    {
    case 1:
        // FCFS_Scheduler(processes, n);
        break;
    case 2:
        SJF_Scheduler(processes, n);
        break;
    case 3:
        // SRTF_Scheduler(processes, n);
        break;
    case 4:
        // MLFQ_Scheduler(processes, n);
        break;
    case 5:
        // RR_Scheduler(processes, n);
        break;
    default:
        printf("Invalid number!.");
        break;
    }
}

int main()
{
    int Dataset_processes_num = 0, user_processes_num = 0, choose;
    char c;
    int num_processes;
    system("clear");
    FILE *fp = fopen("input.txt", "r");

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
    vector<Process> processes(MAX_LINE_LENGTH);

    // Initialize the index for the processes array
    int i = 0;

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        sscanf(line, "%d | %s | %d | %d | %d | %d | %s", &processes[i].process_id, processes[i].process_name, &processes[i].arrival_time, &processes[i].CPU_time, &processes[i].IO_time, &processes[i].IO_start_time, processes[i].pro_specifier);
        processes[i].execution_time = processes[i].CPU_time - processes[i].IO_time;
        processes[i].remaining_time = processes[i].CPU_time;
        i++;
        Dataset_processes_num++;
    }

    fclose(fp);
    i = 0;
    num_processes = Dataset_processes_num;
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
            num_processes += user_processes_num;
            while (user_processes_num--)
            {
                processes[Dataset_processes_num + i].process_id = Dataset_processes_num + i + 1;
                strcpy(processes[Dataset_processes_num + i].process_status, "ready");

                printf("Enter process %d Name: ", i + 1);
                cin >> processes[Dataset_processes_num + i].process_name;

                printf("Enter process %d arrival time: ", i + 1);
                getIntegerOnly(&processes[Dataset_processes_num + i].arrival_time);

                printf("Enter process %d CPU time: ", i + 1);
                getIntegerOnly(&processes[Dataset_processes_num + i].CPU_time);

                printf("Enter process %d IO time: ", i + 1);
                getIntegerOnly(&processes[Dataset_processes_num + i].IO_time);

                if (processes[Dataset_processes_num + i].IO_time != 0)
                {
                    printf("Enter process %d IO start time: ", i + 1);
                    getIntegerOnly(&processes[Dataset_processes_num + i].IO_start_time);
                }

                printf("Enter process %d specifier: ", i + 1);
                cin >> processes[Dataset_processes_num + i].pro_specifier;

                i++;
            }

            choose_scheduler(processes, num_processes);
        }
        else if (choose == 2)
        {
            choose_scheduler(processes, num_processes);
        }
        else
        {
            printf("Invalid number!.\n Please enter a valid number.\n");
        }
    }

    return 0;
}
