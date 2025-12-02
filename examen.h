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




#endif