#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#define MAX 100

const int CHILE_TIME_OFFSET = -4;

//Si se ven muchos copia y pega en el historial es debido a que trabajé en otros repos de prueba, ya que algunas cosas funcionana en algunas funciones y otras no.

struct tipoPaciente {
  char nombre[MAX];
  int edad;
  char sintoma[MAX];
  int prioridad;
  int numeroPaciente;
  int hora;
  int minuto;
  int segundo;
};

void limpiarPantalla() {system("clear");}

void presioneTeclaParaContinuar(){
  puts("Presione alguna tecla para continuar: ");
  getchar();
  getchar();
}

void ordenarPorHora(List *pacientes){
  struct tipoPaciente *Arreglo[MAX];
  struct tipoPaciente *pacienteActual = (struct tipoPaciente *)list_first(pacientes);
  int i = 0;
  while (pacienteActual != NULL) {
      Arreglo[i] = pacienteActual;
      pacienteActual = (struct tipoPaciente *)list_next(pacientes);
      i++;
  }
  //ciclo bubblesort
  for (int j = 0; j < i; j++) {
      for (int k = 0; k < i - j - 1; k++) {
          if (Arreglo[k]->numeroPaciente> Arreglo[k + 1]->numeroPaciente) {
            struct tipoPaciente *temp = Arreglo[k];
              Arreglo[k] = Arreglo[k + 1];
              Arreglo[k + 1] = temp;
          }
      }
  }
  //se llena la lista nuevamente
  list_clean(pacientes);
  for (int j = 0; j < i; j++) {
      list_pushBack(pacientes, Arreglo[j]); 
  }

}

void ordenarLista(List *pacientes) {
    List *listaPrioridadALTA = list_create();
    List *listaPrioridadMEDIA = list_create();
    List *listaPrioridadBAJA = list_create();

    struct tipoPaciente *pActual = (struct tipoPaciente *)list_first(pacientes);
    while (pActual != NULL) {
        if (pActual->prioridad == 3)
            list_pushBack(listaPrioridadALTA, pActual);
        else if (pActual->prioridad == 2)
            list_pushBack(listaPrioridadMEDIA, pActual);
        else{
            list_pushBack(listaPrioridadBAJA, pActual);}

          pActual = (struct tipoPaciente *)list_next(pacientes);
    }

    list_clean(pacientes);
    
    ordenarPorHora(listaPrioridadALTA);
    pActual = (struct tipoPaciente *)list_first(listaPrioridadALTA);
    while (pActual != NULL) {
        list_pushBack(pacientes, pActual);
          pActual = (struct tipoPaciente *)list_next(listaPrioridadALTA);
    }
  
    ordenarPorHora(listaPrioridadMEDIA);
    pActual = (struct tipoPaciente *)list_first(listaPrioridadMEDIA);
    while (pActual != NULL) {
        list_pushBack(pacientes, pActual);
          pActual = (struct tipoPaciente *)list_next(listaPrioridadMEDIA);
    }
  
    ordenarPorHora(listaPrioridadBAJA);
    pActual = (struct tipoPaciente *)list_first(listaPrioridadBAJA);
    while (pActual != NULL) {
        list_pushBack(pacientes, pActual);
          pActual = (struct tipoPaciente *)list_next(listaPrioridadBAJA);
    }

    list_clean(listaPrioridadALTA);
    list_clean(listaPrioridadMEDIA);
    list_clean(listaPrioridadBAJA);
}

void registrar_paciente(List *pacientes) {
  struct tipoPaciente *paciente; 
  char respuesta[MAX];
  int i = 1;
  do{
    paciente = (struct tipoPaciente*) malloc(sizeof(struct tipoPaciente));
    if(paciente == NULL) {printf("No se pudo reservar la memoria correctamente"); exit(EXIT_FAILURE);}

    puts("Ingrese nombre del paciente: ");
    scanf("%s", paciente->nombre);

    puts("Ingrese edad del paciente: ");
    scanf("%d", &paciente->edad);

    puts("Ingrese sintoma del paciente: ");
    scanf("%s", paciente->sintoma);

    time_t current_time = time(NULL);
    struct tm* local_time = localtime(&current_time);
    local_time->tm_hour += CHILE_TIME_OFFSET;
    mktime(local_time);

    paciente->hora =local_time->tm_hour;
    paciente->minuto =local_time->tm_min;
    paciente->segundo =local_time->tm_sec;
    puts("Hora de ingreso del paciente: ");
    printf("%02d:%02d:%02d\n", paciente->hora, paciente->minuto, paciente->segundo);

    paciente->prioridad = 1;
    paciente->numeroPaciente = i;
    list_pushBack(pacientes, paciente);
    puts("¿Desea ingresar más pacientes? si/no");
    scanf("%s", respuesta);

    i++;
  }while(strcmp(respuesta,"no") != 0);
  puts("Regristo de pacientes completado!\n");
  return;
}

struct tipoPaciente *estaEnLista(List *pacientes, char *nombre){

  struct tipoPaciente *paciente = (struct tipoPaciente*) list_first(pacientes);
  for(paciente; paciente != NULL; paciente = list_next(pacientes)){
    if(strcmp(paciente->nombre, nombre) == 0) return paciente;
  }
  return NULL;
}

void asignar_prioridad(List *pacientes){
  struct tipoPaciente* pa = list_first(pacientes);
  if(pa == NULL){ puts("La lista de pacientes está vacia."); return;}
  printf("ASIGNAR PACIENTES POR PRIORIDAD:\n");
  int i = 1;
  for(List *p = list_first(pacientes); p != NULL; p = list_next(pacientes)){
    struct tipoPaciente *paciente = (struct tipoPaciente *)p;
    printf("N°%d) %s --> ", i, paciente->nombre);
    switch(paciente->prioridad){
      case 1:
        printf("Baja\n");
        break;
      case 2:
        printf("Media\n");
        break;
      case 3:
        printf("Alta\n");
        break;
    }
    i++;
  }

  char respuesta[MAX];
  char nombre[MAX];

  do{

    puts("Ingrese nombre del paciente para asignar prioridad: ");
    scanf("%s", nombre);
    struct tipoPaciente *var = estaEnLista(pacientes, nombre);
    if(var != NULL){
      int numero;
      puts("Asigne o mantega prioridad del paciente: ");
      puts("'1' Baja");
      puts("'2' Media");
      puts("'3' Alta");
      int flag = 0;
      do{
        scanf("%d", &numero);
        switch(numero){
          case 1:
            printf("Paciente %s con prioridad Baja\n", var->nombre);
            break;
          case 2:
            var->prioridad = 2;
            printf("Paciente %s con nueva prioridad: Media\n", var->nombre);
            break;
            case 3:
              var->prioridad = 3;
            printf("Paciente %s con nueva prioridad: Alta\n", var->nombre);
          break;
          default:
            puts("Opcion no valida, intente de nuevo.\n");
            flag = 1;
            break;
        }

      }while((numero < 1 || numero > 3) && flag == 0);

    }else printf("Paciente no se encuentra en la lista\n");

    printf("¿Desea cambiar la prioridad de otro paciente? si/no\n");
    scanf("%s", respuesta);

  }while(strcmp(respuesta, "no") != 0);

  return;

}

void mostrarListaEspera(List *pacientes) {

  struct tipoPaciente* pa = list_first(pacientes);
  if(pa == NULL){ puts("La lista de pacientes está vacia."); return;}
  puts("Pacientes en espera:\n");

List *p = list_first(pacientes);
int cont = 1;
for(p = list_first(pacientes); p!= NULL; p = list_next(pacientes)){
  struct tipoPaciente *paciente = (struct tipoPaciente *)p;
  printf("Paciente Nº %d\n", cont);
  printf("Nombre: %s\n", paciente->nombre);
  printf("Edad: %d\n", paciente->edad);
  printf("Síntoma: %s\n", paciente->sintoma);
  switch(paciente->prioridad){
    case 1:
      printf("Prioridad: BAJA\n");
      break;
    case 2:
      printf("Prioridad: MEDIA\n");
      break;
    case 3:
      printf("Prioridad: ALTA\n");
      break;
  }
  printf("Hora de llegada: %02d:%02d:%02d\n\n", paciente->hora, paciente->minuto, paciente->segundo);
  cont++;
  }

}

void atenderSiguientePaciente(List *pacientes){
  struct tipoPaciente* pa = list_first(pacientes);
  if(pa == NULL){ puts("La lista de pacientes está vacia."); return;}
  puts("Paciente por atender:\n");
  struct tipoPaciente* pActual = list_first(pacientes);
  printf("Nombre: %s\n", pActual->nombre);
  printf("Edad: %d\n", pActual->edad);
  printf("Síntoma: %s\n", pActual->sintoma);
  switch(pActual->prioridad){
    case 1:
      printf("Prioridad: BAJA\n");
      break;
    case 2:
      printf("Prioridad: MEDIA\n");
      break;
    case 3:
      printf("Prioridad: ALTA\n");
      break;
  }
    list_popFront(pacientes);
}

void mostrarPacientesPrioridad(List *pacientes) {
    struct tipoPaciente *p = list_first(pacientes);
    if (p == NULL) {
        puts("La lista de pacientes está vacía.");
        return;
    }

    int respuesta = 0;
    puts("Ingrese prioridad a mostrar:");
    puts("'1' Baja");
    puts("'2' Media");
    puts("'3' Alta");

    scanf("%d", &respuesta);

    int cont = 1;
    while (p != NULL) {
        struct tipoPaciente *paciente = (struct tipoPaciente *)p;

        if (paciente->prioridad == respuesta) {
            printf("Paciente Nº %d\n", cont);
            printf("Nombre: %s\n", paciente->nombre);
            printf("Edad: %d\n", paciente->edad);
            printf("Síntoma: %s\n", paciente->sintoma);

            switch (paciente->prioridad) {
                case 1:
                    printf("Prioridad: BAJA\n");
                    break;
                case 2:
                    printf("Prioridad: MEDIA\n");
                    break;
                case 3:
                    printf("Prioridad: ALTA\n");
                    break;
            }

            printf("\n");
            cont++;
        }

        p = list_next(pacientes); 
    }
    if (cont == 1) {
        puts("No hay pacientes con esa prioridad en la lista.");
    }
}

void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

int main() {
  char opcion;
  List*pacientes = list_create(); 
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); 

    switch (opcion) {
    case '1':
      registrar_paciente(pacientes);
      break;
    case '2':
      asignar_prioridad(pacientes);
      ordenarLista(pacientes);
      break;
    case '3':
      mostrarListaEspera(pacientes);
      break;
    case '4':
      atenderSiguientePaciente(pacientes);
      break;
    case '5':
      mostrarPacientesPrioridad(pacientes);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      return 0;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  list_clean(pacientes);

  return 0;
}
