#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "examen.h"

//Implementacion de la cola

//Inicia una cola completamente vacia
void queue_init(Queue *q) {
    q->front = NULL;
    q->rear  = NULL;
    q->size  = 0;
}

//verifica si en verdad esta vacia 
bool queue_is_empty(const Queue *q) {
    return (q->front == NULL);
}
//Devuelve la cantidad de elementos en la cola
size_t queue_size(const Queue *q) {
    return q->size;
}

//Se usara la funcion "queue_enqueue" de la profesora para adaptarlo a nuestro programa
int queue_enqueue(Queue *q, int ID, const char *nombre, int prioridad) {
    NodePaciente *newNode = (NodePaciente *)malloc(sizeof(NodePaciente));
    if (newNode == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria en queue_enqueue.\n");
        return -1;
    }

    newNode->ID = ID;
    newNode->prioridad = prioridad;
strncpy(newNode->nombre, nombre, NOMBRE - 1);
    newNode->nombre[NOMBRE - 1] = '\0';
    newNode->next = NULL;

    if (queue_is_empty(q)) {
        q->front = newNode;
        q->rear  = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }

    q->size++;
    return 0;
}


//Se usara la funcion "queue_dequeue" de la profesora para adaptarlo a nuestro programa
int queue_dequeue(Queue *q, int *outId, char *outNombre, int *outPrioridad) {
    if (queue_is_empty(q)) {
        fprintf(stderr, "Error: no se puede hacer dequeue en una cola vacía.\n");
        return -1;
    }

    NodePaciente *temp = q->front;

    if (outId != NULL)        *outId = temp->ID;
    if (outNombre != NULL)    strncpy(outNombre, temp->nombre, NOMBRE);
    if (outPrioridad != NULL) *outPrioridad = temp->prioridad;

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    q->size--;
    return 0;
}

//Se usara la funcion "queue_clear" de la profesora para adaptarlo a nuestro programa
void queue_clear(Queue *q) {
    NodePaciente *current = q->front;
    while (current != NULL) {
        NodePaciente *next = current->next;
        free(current);
        current = next;
    }

    q->front = NULL;
    q->rear  = NULL;
    q->size  = 0;
}

//Inicia una cola por cada prioridad
void sistema_init(Sistema *s) {
    if (s == NULL) return;

    for (int i = 0; i < PRIORIDADES; i++) {
        queue_init(&s->colas[i]);
    }
    s->atendidos = 0;
}

//Recorre todas las colas en busca de un ID para verificar si existe
bool sistema_existe_id(const Sistema *s, int ID) {
    if (s == NULL) return false;

    for (int p = 0; p < PRIORIDADES; p++) {
        NodePaciente *cur = s->colas[p].front;
        while (cur != NULL) {
            if (cur->ID == ID) {
                return true;
            }
            cur = cur->next;
        }
    }
    return false;
}

//Añade a un paciente a su respectiva cola segun su prioridad si este es valido y no esta. 
int sistema_insertar(Sistema *s, int ID, const char *nombre, int prioridad) {
    if (s == NULL) return -1;

    if (prioridad < 0 || prioridad >= PRIORIDADES) {
        fprintf(stderr, "Error: prioridad inválida (%d).\n", prioridad);
        return -1;
    }

    if (sistema_existe_id(s, ID)) {
        fprintf(stderr, "Error: el ID %d ya existe en el sistema.\n", ID);
        return -1;
    }

    return queue_enqueue(&s->colas[prioridad], ID, nombre, prioridad);
}