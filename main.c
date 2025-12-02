#include <stdio.h>
#include "examen.h"

int main(void) {
    Sistema s;
    sistema_init(&s);

    printf("=== Inserción inicial de pacientes ===\n");
    sistema_insertar(&s, 1, "Pepe",    2);
    sistema_insertar(&s, 2, "Fifi",   0);
    sistema_insertar(&s, 3, "Carolina",  1);
    sistema_insertar(&s, 4, "George", 0);
    sistema_insertar(&s, 5, "Adrian",  3);
    sistema_insertar(&s, 6, "Javier",   4);

    printf("Prueba de ID repetido: \n");
    sistema_insertar(&s, 2, "FifiDuplicado", 1);

    sistema_imprimir(&s);

    printf("Pruebas de búsqueda: \n");
    printf("Buscar ID 3 (existe):\n");
    sistema_buscar(&s, 3);

    printf("\nBuscar ID 99 (no existe):\n");
    sistema_buscar(&s, 99);

    printf("Atender dos pacientes: \n");
    sistema_atender(&s);
    sistema_atender(&s);

    sistema_imprimir(&s);

    printf("Prueba de cancelación en prioridad 1: \n");
    sistema_insertar(&s, 100, "Ini",   1);
    sistema_insertar(&s, 101, "Medio", 1);
    sistema_insertar(&s, 102, "Final", 1);

    sistema_imprimir(&s);

    printf("Pureba de cancelar paciente al inicio: \n");
    sistema_cancelar(&s, 3);
    sistema_imprimir(&s);

    printf("Prueba de cancelar paciente en el medio: \n");
    sistema_cancelar(&s, 101);
    sistema_imprimir(&s);

    printf("=Prueba de cancelar paciente en el final: \n");
    sistema_cancelar(&s, 102);
    sistema_imprimir(&s);

    printf("Prueba de cancelar paciente inexistente \n");
    sistema_cancelar(&s, 42);

    sistema_estadisticas(&s);

    printf("Prueba de guardar en el txt \n");
    sistema_guardar(&s, "pacientes.txt");

    sistema_liberar(&s);

    return 0;
}