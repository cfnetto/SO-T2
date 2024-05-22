#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "list.h"
#include "task.h"

// Função para adicionar uma tarefa à lista de aptos
void add_task(Task task);

// Função para realizar o escalonamento (Round-Robin com prioridade)
void schedule_rr_p();

// Função para realizar o escalonamento (Earliest Deadline First)
void schedule_edf();

#endif /* SCHEDULER_H */
