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


