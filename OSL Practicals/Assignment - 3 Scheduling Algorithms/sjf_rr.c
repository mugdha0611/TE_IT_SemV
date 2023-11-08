#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process{
	int id;
	int arrival_time;
	int burst_time;
	int remaining_time;
	int completion_time;
	int turnaround_time;
	int waiting_time;
	
};

// Function to find the process with the shortest remaining time
int findShortestJob(struct Process processes[], int n, int current_time)
{
    int shortest_job = -1;
    int shortest_time = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time < shortest_time && processes[i].remaining_time > 0)
        {
            shortest_job = i;
            shortest_time = processes[i].remaining_time;
        }
    }

    return shortest_job;
}

// Function to perform Round Robin scheduling
void roundRobin(struct Process processes[], int n, int time_quantum)
{
    int completed = 0;
    int current_time = 0;
    int turnaround_time[n];
    int waiting_time[n];

    for (int i = 0; i < n; i++)
    {
        waiting_time[i] = 0;
    }

    printf("Gantt Chart (Round Robin):\n");
    printf("|");
    while (completed < n)
    {
        int shortest_job = findShortestJob(processes, n, current_time);

        if (shortest_job == -1)
        {
            current_time++;
        }
        else
        {
            char process_id[5];
            sprintf(process_id, "P%d", processes[shortest_job].id);
            printf("%s|", process_id);

            int execution_time = (processes[shortest_job].remaining_time > time_quantum) ? time_quantum : processes[shortest_job].remaining_time;
            processes[shortest_job].remaining_time -= execution_time;
            current_time += execution_time;

            if (processes[shortest_job].remaining_time == 0)
            {
                completed++;
                turnaround_time[shortest_job] = current_time - processes[shortest_job].arrival_time;
                waiting_time[shortest_job] = turnaround_time[shortest_job] - processes[shortest_job].burst_time;
            }
        }
    }
    printf("\n");

    // Print the results in a tabular format
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, waiting_time[i], turnaround_time[i]);
    }
}

// Function to perform Shortest Job First (Preemptive) scheduling
void shortestJobFirstPreemptive(struct Process processes[], int n)
{
    int completed = 0;
    int current_time = 0;
    int turnaround_time[n];
    int waiting_time[n];

    for (int i = 0; i < n; i++)
    {
        waiting_time[i] = 0;
    }

    printf("Gantt Chart (Shortest Job First - Preemptive):\n");
    printf("|");
    while (completed < n)
    {
        int shortest_job = findShortestJob(processes, n, current_time);

        if (shortest_job == -1)
        {
            current_time++;
        }
        else
        {
            char process_id[5];
            sprintf(process_id, "P%d", processes[shortest_job].id);
            printf("%s|", process_id);

            processes[shortest_job].remaining_time--;
            current_time++;

            if (processes[shortest_job].remaining_time == 0)
            {
                completed++;
                turnaround_time[shortest_job] = current_time - processes[shortest_job].arrival_time;
                waiting_time[shortest_job] = turnaround_time[shortest_job] - processes[shortest_job].burst_time;
            }
        }
    }
    printf("\n");

    // Print the results in a tabular format
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, waiting_time[i], turnaround_time[i]);
    }
}

// Function to perform Shortest Job First (Non-Preemptive) scheduling
void shortestJobFirstNonPreemptive(struct Process processes[], int n)
{
    int current_time = 0;

    // Sort processes based on their arrival times
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    printf("Gantt Chart (Shortest Job First - Non-Preemptive):\n");
    printf("|");
    int completed = 0;

    while (completed < n)
    {
        int shortest_job = -1;
        int shortest_burst = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && processes[i].completion_time == 0 && processes[i].burst_time < shortest_burst)
            {
                shortest_job = i;
                shortest_burst = processes[i].burst_time;
            }
        }

        if (shortest_job == -1)
        {
            current_time++;
        }
        else
        {
            char process_id[5];
            sprintf(process_id, "P%d", processes[shortest_job].id);
            printf("%s|", process_id);

            current_time += processes[shortest_job].burst_time;
            processes[shortest_job].completion_time = current_time;
            processes[shortest_job].turnaround_time = processes[shortest_job].completion_time - processes[shortest_job].arrival_time;
            processes[shortest_job].waiting_time = processes[shortest_job].turnaround_time - processes[shortest_job].burst_time;

            completed++;
        }
    }
    printf("\n");

    // Print the results in a tabular format
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main()
{
    int n;
    int choice;

    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    while (1)
    {
        printf("\nSelect a scheduling algorithm:\n");
        printf("1. Round Robin\n");
        printf("2. Shortest Job First (Preemptive)\n");
        printf("3. Shortest Job First (Non-Preemptive)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int time_quantum;
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &time_quantum);
            roundRobin(processes, n, time_quantum);
        }
        break;
        case 2:
            shortestJobFirstPreemptive(processes, n);
            break;
        case 3:
            shortestJobFirstNonPreemptive(processes, n);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}