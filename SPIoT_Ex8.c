//Process Scheduling (Round Robin) in an IoT Environment (Arduino IDE)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TIME_QUANTUM 10
#define MAX_TASKS 5

typedef struct {
    int pid;             // Process ID
    int burst_time;      // Remaining burst time
    int original_time;   // Original burst time for display
} Task;

Task task_queue[MAX_TASKS];

// Function to add a task to the queue
void add_task(int pid, int burst_time) {
    Task task;
    task.pid = pid;
    task.burst_time = burst_time;
    task.original_time = burst_time; // Store original burst time
    task_queue[pid] = task;
}

// Function to execute a task
void execute_task(int pid) {
    // Calculate the time to execute
    int execution_time = (task_queue[pid].burst_time > TIME_QUANTUM) ? TIME_QUANTUM : task_queue[pid].burst_time;
    
    printf("Executing task %d for %d milliseconds\n", task_queue[pid].pid, execution_time);
    usleep(execution_time * 1000); // Convert to microseconds
    task_queue[pid].burst_time -= execution_time; // Deduct the execution time
}

// Round Robin scheduling algorithm
void rr_scheduling() {
    int tasks_remaining = MAX_TASKS; // Counter for remaining tasks

    while (tasks_remaining > 0) {
        for (int i = 0; i < MAX_TASKS; i++) {
            if (task_queue[i].burst_time > 0) {
                execute_task(i);
                
                // If burst time is finished
                if (task_queue[i].burst_time <= 0) {
                    printf("Task %d completed\n", task_queue[i].pid);
                    task_queue[i].burst_time = 0; // Set remaining time to zero
                    tasks_remaining--; // Decrement remaining tasks
                }
            }
        }
    }
}

int main() {
    // Adding tasks with PID and burst times
    add_task(0, 20);
    add_task(1, 30);
    add_task(2, 10);
    add_task(3, 25);
    add_task(4, 15);
    
    // Start Round Robin Scheduling
    rr_scheduling();
    
    return 0;
}
