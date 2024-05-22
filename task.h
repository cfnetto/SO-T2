#ifndef TASK_H
#define TASK_H

// Definição da estrutura da tarefa
typedef struct
{
    int id;
    int priority;       // Prioridade da tarefa
    int arrival_time;   // Tempo de chegada
    int execution_time; // Tempo de execução
    int deadline;       // Deadline (apenas para EDF)
} Task;

#endif /* TASK_H */
