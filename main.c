#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "scheduler.h"

#define NUM_PRIORITIES 3
#define MAX_TASKS_PER_PRIORITY 2
#define TIME_SLICE 10

// Estrutura para representar uma tarefa na lista de aptos
typedef struct
{
    Task task;
    struct TaskNode *next;
} TaskNode;

// Lista de aptos (múltiplas filas para diferentes prioridades)
TaskNode *ready_queues[NUM_PRIORITIES];

// Mutex para exclusão mútua ao acessar a lista de aptos
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Função para adicionar uma tarefa à lista de aptos
void add_task(Task task)
{
    TaskNode *new_task_node = (TaskNode *)malloc(sizeof(TaskNode));
    new_task_node->task = task;
    new_task_node->next = NULL;

    // Adiciona a tarefa à lista de aptos correspondente à sua prioridade
    pthread_mutex_lock(&mutex);
    int priority = task.priority - 1; // Prioridade começa em 1
    if (ready_queues[priority] == NULL)
    {
        ready_queues[priority] = new_task_node;
    }
    else
    {
        TaskNode *current = ready_queues[priority];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_task_node;
    }
    pthread_mutex_unlock(&mutex);
}

// Função para realizar o escalonamento (Round-Robin com prioridade)
void schedule_rr_p()
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        // Percorre as filas de aptos para encontrar a primeira tarefa disponível
        TaskNode *selected_task_node = NULL;
        for (int i = 0; i < NUM_PRIORITIES; i++)
        {
            if (ready_queues[i] != NULL)
            {
                selected_task_node = ready_queues[i];
                ready_queues[i] = selected_task_node->next;
                break;
            }
        }
        pthread_mutex_unlock(&mutex);

        // Se encontrou uma tarefa, executa
        if (selected_task_node != NULL)
        {
            printf("Executing task %d with priority %d\n", selected_task_node->task.id, selected_task_node->task.priority);
            sleep(TIME_SLICE);
            free(selected_task_node);
        }
        else
        {
            // Se não encontrou nenhuma tarefa, aguarda
            printf("No tasks available. Waiting...\n");
            sleep(1);
        }
    }
}

// Função para realizar o escalonamento (Earliest Deadline First)
void schedule_edf()
{
    // Implemente aqui...
}
