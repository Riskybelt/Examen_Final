#ifndef EXAMEN_H
#define EXAMEN_H 

#include <stdio.h>
#include <stdbool.h>

#define NOMBRE 50
#define PRIORIDADES 5

//Nodo de pacientes
typedef struct NodePaciente {
    int ID;
    char nombre[NOMBRE];
    int prioridad;
    struct NodePaciente *next;
} NodePaciente;

//Cola de pacientes que contempla el primer paciente, el ultimo y el tamaño de la cola
typedef struct {
    NodePaciente *front;   
    NodePaciente *rear;    
    size_t size;           
} Queue;

//Estructra que lleva el control de prioridad y pacientes atendidos
typedef struct {
    Queue colas[PRIORIDADES];  
    size_t atendidos;           
} Sistema;


//Aca se usaran los prototipos brindados por los archivos en mediacion

/* Inicializa una cola vacia */
void queue_init(Queue *q);

/* Devuelve true si la cola esta vacia */
bool queue_is_empty(const Queue *q);

/* Devuelve la cantidad de elementos en la cola */
size_t queue_size(const Queue *q);

/* Encola un paciente al final de la cola.
   Retorna 0 si todo bien, -1 si error de memoria. */
int queue_enqueue(Queue *q, int id, const char *nombre, int prioridad);

/* Desencola el paciente del frente.
   Guarda los datos en outId, outNombre y outPrioridad.
   Retorna 0 si éxito, -1 si la cola estaba vacía. */
int queue_dequeue(Queue *q, int *outId, char *outNombre, int *outPrioridad);

/* Elimina todos los elementos de la cola y libera la memoria */
void queue_clear(Queue *q);

#endif