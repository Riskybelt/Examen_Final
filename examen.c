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

/*Atiende al paciente en la cola de mayor prioridad, muestra su info 
y lleva un conteo de atendidos*/
int sistema_atender(Sistema *s) {
    if (s == NULL) return -1;

    for (int p= 0; p < PRIORIDADES; p++) {
        if (!queue_is_empty(&s->colas[p])) {

            int ID, prioridad;
            char nombre[NOMBRE];

            if (queue_dequeue(&s->colas[p], &ID, nombre, &prioridad) == 0) {
                printf("Paciente atendido:\n");
                printf("  ID: %d\n", ID);
                printf("  Nombre: %s\n", nombre);
                printf("  Prioridad: %d\n", prioridad);

                s->atendidos++;
                return 0;
            } else {
                return -1;
            }
        }
    }

    printf("No hay pacientes en espera.\n");
    return -1;
}

//Saca a un paciente de la cola y no lo atiende
int sistema_cancelar(Sistema *s, int ID) {
    if (s == NULL) return -1;

    for (int p = 0; p < PRIORIDADES; p++) {
        Queue *q = &s->colas[p];
        NodePaciente *prev = NULL;
        NodePaciente *cur  = q->front;

        while (cur != NULL) {
            if (cur->ID == ID) {
                if (prev == NULL) {
                    q->front = cur->next;
                    if (q->front == NULL) {
                        q->rear = NULL;
                    }
                } else {
                    prev->next = cur->next;
                    if (cur== q->rear) {
                        q->rear = prev;
                    }
                }

                free(cur);
                q->size--;

                printf("Paciente con ID: %d eliminado del sistema.\n", ID);
                return 0;
            }
            prev = cur;
            cur= cur->next;
        }
    }
    printf("Paciente con ID: %d no se encuentra en el sistema.\n", ID);
    return -1;
}

//Imprime la informacion de un paciente 
void sistema_buscar(const Sistema *s, int ID) {
    if (s == NULL) return;

    for (int p = 0; p < PRIORIDADES; p++) {
        NodePaciente *cur = s->colas[p].front;
        while (cur != NULL) {
            if (cur->ID ==ID) {
                printf("Paciente encontrado:\n");
                printf(" ID: %d\n", cur->ID);
                printf(" Nombre: %s\n", cur->nombre);
                printf(" Prioridad: %d\n", cur->prioridad);
                return;
            }
            cur = cur->next;
        }
    }

    printf("Paciente con ID: %d no existe en el sistema.\n", ID);
}

//Imprime el estado completo del sistema (sala de emergecias)
void sistema_imprimir(const Sistema *s) {
    if (s == NULL) return;

    printf("Estado de la sala: \n");

    for (int p = 0; p < PRIORIDADES; p++) {
        printf("Prioridad %d:\n", p);

        if (queue_is_empty(&s->colas[p])) {
            printf("  (sin pacientes)\n");
            continue;
        }

        NodePaciente *cur = s->colas[p].front;
        while (cur != NULL) {
            printf("  ID: %d, Nombre: %s\n", cur->ID, cur->nombre);
            cur = cur->next;
        }
    }

}

/*Imprime la cantidad de pacientes en cada prioridad y de paso 
cuantos an sido atendidos (aprobechando que tenemos el conteo global)*/
void sistema_estadisticas(const Sistema *s) {
    if (s == NULL) return;

    printf("Estadísticas del sistema: \n");
    for (int p = 0; p < PRIORIDADES; p++) {
        printf("Prioridad %d: %zu pacientes\n", p, queue_size(&s->colas[p]));
    }
    printf("Pacientes atendidos: %zu\n", s->atendidos);
}

