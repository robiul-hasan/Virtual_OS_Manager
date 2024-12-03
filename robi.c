#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PROCESSES 5
#define MEMORY_SIZE 1024  // total virtual memory size for simulation

// Define a structure to represent a process
typedef struct {
    int pid;
    char name[20];
    int memory;      // Memory required by the process
    char state[20];  // States: "Running", "Waiting", "Terminated"
} Process;

// Global variables
Process processes[MAX_PROCESSES];
int process_count = 0;
int memory_used = 0;

// Function to create a new process
void create_process(char *name, int memory) {
    if (process_count >= MAX_PROCESSES) {
        printf("Process limit reached. Cannot create more processes.\n");
        return;
    }
    if (memory_used + memory > MEMORY_SIZE) {
        printf("Not enough memory available to create process %s.\n", name);
        return;
    }

    Process new_process;
    new_process.pid = process_count + 1;
    strcpy(new_process.name, name);
    new_process.memory = memory;
    strcpy(new_process.state, "Running");

    processes[process_count++] = new_process;
    memory_used += memory;

    printf("Process %s created with PID %d, using %d memory.\n", name, new_process.pid, memory);
}

// Function to terminate a process
void terminate_process(int pid) {
    int found = 0;
    for (int i = 0; i < process_count; i++) {
        if (processes[i].pid == pid) {
            printf("Terminating process %s with PID %d.\n", processes[i].name, pid);
            memory_used -= processes[i].memory;
            strcpy(processes[i].state, "Terminated");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Process with PID %d not found.\n", pid);
    }
}

// Function to display the current status of all processes
void display_processes() {
    printf("\n--- Process List ---\n");
    printf("PID\tName\t\tMemory\tState\n");
    for (int i = 0; i < process_count; i++) {
        printf("%d\t%s\t\t%d\t%s\n", processes[i].pid, processes[i].name, processes[i].memory, processes[i].state);
    }
    printf("Total memory used: %d / %d\n", memory_used, MEMORY_SIZE);
}

// Main function to simulate the Virtual OS Manager
int main() {
    int choice, memory, pid;
    char name[20];

    while (1) {
        printf("\n--- Virtual OS Manager ---\n");
        printf("1. Create Process\n");
        printf("2. Terminate Process\n");
        printf("3. Display Processes\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter process name: ");
                scanf("%s", name);
                printf("Enter memory required: ");
                scanf("%d", &memory);
                create_process(name, memory);
                break;

            case 2:
                printf("Enter PID of process to terminate: ");
                scanf("%d", &pid);
                terminate_process(pid);
                break;

            case 3:
                display_processes();
                break;

            case 4:
                printf("Exiting Virtual OS Manager.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
