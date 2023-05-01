#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tama 100

typedef struct Tarea
{
    int TareaID;
    char *Descripcion;
    int Duracion;
}Tarea;

void mostrarTarea(Tarea *t);
void mostrarTareas(Tarea **t, int cant);

//Programa Principal

int main(){ 

    int cant, aux;
    char buff[tama];

    printf("Ingrese la Cantidad de tareas: ");
    scanf("%d", &cant);

    Tarea **tareasPendientes;
    Tarea **tareasRealizadas;

    tareasPendientes=(Tarea**)malloc(sizeof(Tarea*)*cant);
    tareasRealizadas=(Tarea**)malloc(sizeof(Tarea*)*cant);

    for (int i=0; i<cant; i++)
    {
        tareasPendientes[i]=NULL;
        tareasRealizadas[i]=NULL;
    }

    for (int i=0; i<cant; i++)
    {
        printf("\n--------CARGAR TAREA[%d]--------\n",i+1);

        tareasPendientes[i] = (Tarea *) malloc(sizeof(Tarea) * 1);

        tareasPendientes[i]->TareaID=i+1;

        fflush(stdin);
        printf("Ingrese la Descripcion: ");
        gets(buff);
        tareasPendientes[i]->Descripcion=malloc(sizeof(char)*(strlen(buff)+1));
        strcpy(tareasPendientes[i]->Descripcion, buff);

        printf("Ingrese Duracion de la Tarea: ");
        scanf("%d", &tareasPendientes[i]->Duracion);
    }
    
    for (int i=0; i<cant; i++)
    {
        printf("\n-------- TAREA[%d] --------\n",i+1);
        mostrarTarea(tareasPendientes[i]);

        do
        {
            printf("\nRealizo la Tarea? (Si=1), (No=0): ");
            scanf("%d", &aux);

        } while (aux!=1 && aux!=0);

        if(aux==1){
            tareasRealizadas[i]=tareasPendientes[i];
            tareasPendientes[i]=NULL;
        }
    }

    printf("\n-----TAREAS REALIZADAS-----\n");
    mostrarTareas(tareasRealizadas, cant);
    
    printf("\n-----TAREAS PENDIENTES-----\n");
    mostrarTareas(tareasPendientes, cant);
    
    return 0;
}

//Funcion para mostrar la Tarea

void mostrarTarea(Tarea *t){

    printf("ID Tarea: %d\n", t->TareaID);
    printf("Descripcion: %s\n", t->Descripcion);
    printf("Duracion: %d\n", t->Duracion);

}

//Funcion para mostrar Tareas pendientes y realizadas

void mostrarTareas(Tarea **t, int cant){

    for (int i=0; i<cant; i++)
    {
        if(t[i]!=NULL){
            printf("\n-------- TAREA[%d] --------\n",i+1);
            mostrarTarea(t[i]);
        }
    }
}