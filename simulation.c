/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PROCESSES 10


typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;  
} Process;

int main() {
    
    srand(time(NULL));

    
    Process processes[NUM_PROCESSES];

    printf("Generated Processes:\n");
    printf("Process ID | Arrival Time | Burst Time | Priority\n");
    printf("----------------------------------------------\n");

    for (int i = 0; i < NUM_PROCESSES; i++) {
        processes[i].process_id = i + 1;
        processes[i].arrival_time = rand() % 10; 
        processes[i].burst_time = (rand() % 10) + 1; 
        processes[i].priority = (i % 3 == 0) ? 0 : 1; 

        printf("    %2d    |       %2d      |     %2d     |    %1d\n",
               processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].priority);
    }

    return 0;
}
*/






/*#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char name;
    int priority;
    int burst_time;
} Task;


typedef struct {
    Task *tasks;
    int front, rear, size;
} Queue;


Queue* createQueue(int size) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->tasks = (Task*)malloc(sizeof(Task) * size);
    queue->front = queue->rear = -1;
    queue->size = size;
    return queue;
}


int isEmpty(Queue* queue) {
    return queue->front == -1;
}


int isFull(Queue* queue) {
    return (queue->rear + 1) % queue->size == queue->front;
}


void enqueue(Queue* queue, Task task) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % queue->size;
    }
    queue->tasks[queue->rear] = task;
}


Task dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        Task empty_task = {0, 0, 0};
        return empty_task;
    }
    Task task = queue->tasks[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->size;
    }
    return task;
}

int main() {
    int num_tasks;
    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    Queue* task_queue = createQueue(num_tasks);

    for (int i = 0; i < num_tasks; i++) {
        Task task;
        printf("Enter the task name (A, B, C, etc.): ");
        scanf(" %c", &task.name);
        printf("Enter the priority (1 for system-critical, 2 for user, etc.): ");
        scanf("%d", &task.priority);
        printf("Enter the burst time (execution time): ");
        scanf("%d", &task.burst_time);
        enqueue(task_queue, task);
    }

    printf("\nTask execution order:\n");
    int current_time = 0;
    while (!isEmpty(task_queue)) {
        Task highest_priority_task = dequeue(task_queue);
        printf("Executing Task %c (Priority: %d, Burst Time: %d)\n", highest_priority_task.name, highest_priority_task.priority, highest_priority_task.burst_time);
        current_time += highest_priority_task.burst_time;
    }

    return 0;
}*/


/*#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name;
    int priority;
    int burst_time;
    int arrival_time;
    int start_time;
    int completion_time;
    int waiting_time;
} Task;

typedef struct {
    Task *tasks;
    int front, rear, size;
} Queue;

Queue* createQueue(int size) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->tasks = (Task*)malloc(sizeof(Task) * size);
    queue->front = queue->rear = -1;
    queue->size = size;
    return queue;
}

int isEmpty(Queue* queue) {
    return queue->front == -1;
}

int isFull(Queue* queue) {
    return (queue->rear + 1) % queue->size == queue->front;
}

void enqueue(Queue* queue, Task task) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % queue->size;
    }
    queue->tasks[queue->rear] = task;
}

Task dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        Task empty_task = {0, 0, 0};
        return empty_task;
    }
    Task task = queue->tasks[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->size;
    }
    return task;
}

int main() {
    int num_tasks;
    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    Queue* task_queue = createQueue(num_tasks);

    for (int i = 0; i < num_tasks; i++) {
        Task task;
        printf("Enter the task name (A, B, C, etc.): ");
        scanf(" %c", &task.name);
        printf("Enter the priority (1 for system-critical, 2 for user, etc.): ");
        scanf("%d", &task.priority);
        printf("Enter the burst time (execution time): ");
        scanf("%d", &task.burst_time);
        task.arrival_time = 0; 
        task.start_time = -1;
        task.completion_time = -1;
        task.waiting_time = 0;
        enqueue(task_queue, task);
    }

    int current_time = 0;
    int total_waiting_time = 0;
    int total_completion_time = 0;

    printf("\nTask execution order:\n");
    while (!isEmpty(task_queue) && current_time < 100) {
        Task highest_priority_task = dequeue(task_queue);
        highest_priority_task.start_time = current_time;
        int execution_time = (highest_priority_task.burst_time < 100 - current_time) ? highest_priority_task.burst_time : (100 - current_time);
        highest_priority_task.burst_time -= execution_time;
        current_time += execution_time;
        highest_priority_task.completion_time = current_time;
        total_waiting_time += highest_priority_task.waiting_time;
        total_completion_time += highest_priority_task.completion_time;
        printf("Executing Task %c (Priority: %d, Burst Time: %d, Completion Time: %d)\n", highest_priority_task.name, highest_priority_task.priority, execution_time, highest_priority_task.completion_time);

    
        if (highest_priority_task.burst_time > 0) {
            enqueue(task_queue, highest_priority_task);
        }
    }


    float average_waiting_time = (float)total_waiting_time / num_tasks;
    float average_completion_time = (float)total_completion_time / num_tasks;

    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Completion Time: %.2f\n", average_completion_time);

    return 0;
}*/



/*#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name;
    int priority;
    int burst_time;
} Task;


typedef struct {
    Task *tasks;
    int front, rear, size;
} Queue;


Queue* createQueue(int size) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->tasks = (Task*)malloc(sizeof(Task) * size);
    queue->front = queue->rear = -1;
    queue->size = size;
    return queue;
}


int isEmpty(Queue* queue) {
    return queue->front == -1;
}


int isFull(Queue* queue) {
    return (queue->rear + 1) % queue->size == queue->front;
}


void enqueue(Queue* queue, Task task) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % queue->size;
    }
    queue->tasks[queue->rear] = task;
}


Task dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        Task empty_task = {0, 0, 0};
        return empty_task;
    }
    Task task = queue->tasks[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->size;
    }
    return task;
}

int main() {
    int num_tasks;
    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    Queue* task_queue = createQueue(num_tasks);

    for (int i = 0; i < num_tasks; i++) {
        Task task;
        printf("Enter the task name (A, B, C, etc.): ");
        scanf(" %c", &task.name);
        printf("Enter the priority (1 for system-critical, 2 for user, etc.): ");
        scanf("%d", &task.priority);
        printf("Enter the burst time (execution time): ");
        scanf("%d", &task.burst_time);
        enqueue(task_queue, task);
    }

    printf("\nTask execution order:\n");
    int current_time = 0;
    while (!isEmpty(task_queue)) {
        Task highest_priority_task = dequeue(task_queue);
        printf("Executing Task %c (Priority: %d, Burst Time: %d)\n", highest_priority_task.name, highest_priority_task.priority, highest_priority_task.burst_time);
        current_time += highest_priority_task.burst_time;
    }

    return 0;
}*/


#include <stdio.h>
#include <unistd.h>

// Process struct to represent exams
typedef struct {
    char name[10];
    int period;
    int processing_time;
    int deadline;
    int priority;
} Process;

// Function to simulate an exam
void runExam(Process *exam, int time) {
    printf("%s exam started at time %d\n", exam->name, time);
    sleep(exam->processing_time);
    printf("%s exam completed at time %d\n", exam->name, time + exam->processing_time);
}

int main() {
    Process jee = {"JEE", 50, 20, 50, 1};
    Process gate = {"GATE", 100, 35, 100, 2};

    int time = 0;

    while (1) {
        if (time % jee.period == 0) {
            runExam(&jee, time);
        }
        if (time % gate.period == 0) {
            runExam(&gate, time);
        }

        // Simulate time passing
        sleep(1);
        time++;

        // Exit the simulation after a certain number of iterations
        if (time > 200) {
            break;
        }
    }

    return 0;
} 


