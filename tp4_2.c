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
Tarea * BuscarTareaPorId(Tarea **tareaP, Tarea **tareaR, int cant, int id);
Tarea * BuscarTareaPorPalabra(Tarea **tareaP, Tarea **tareaR, int cant, char clave[]);

//Programa Principal

int main(){ 

    int cant, aux, id;
    char buff[tama], buff2[tama];
    char *clave;
    Tarea *tareaEncontrada=NULL;

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

    printf("\nBuscar Tarea, Ingrese un ID: ");
    scanf("%d", &id);

    tareaEncontrada=BuscarTareaPorId(tareasPendientes, tareasRealizadas, cant, id);

    if(tareaEncontrada != NULL){

        printf("\n-----TAREA ENCONTRADA-----\n");
        mostrarTarea(tareaEncontrada);

    }else{
        printf("\n-----NO SE ENCONTRO LA TAREA -----\n");
    }

    fflush(stdin);
    printf("\nBuscar Tarea, Ingrese palabra clave: ");
    gets(buff2);
    clave=(char*)malloc(sizeof(char)* (strlen(buff2)+1) );
    strcpy(clave,buff2);

    tareaEncontrada=BuscarTareaPorPalabra(tareasPendientes, tareasRealizadas, cant, clave);

    if(tareaEncontrada != NULL){

        printf("\n-----TAREA ENCONTRADA-----\n");
        mostrarTarea(tareaEncontrada);

    }else{
        printf("\n-----NO SE ENCONTRO LA TAREA -----\n");
    }

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

//Funcion para Buscar una Tarea por ID

Tarea * BuscarTareaPorId(Tarea **tareaP, Tarea **tareaR, int cant, int id){

    if(tareaP!=NULL && tareaR!=NULL){

        for (int i=0; i<cant; i++)
        {
            if(tareaP[i]!=NULL && tareaP[i]->TareaID==id){

                return(tareaP[i]);

            }else if (tareaR[i]!=NULL && tareaR[i]->TareaID==id){

                return(tareaR[i]);
            }
        }
    }
    return(NULL);
}

//FUncion para Buscar una Tarea por palabra clave

Tarea * BuscarTareaPorPalabra(Tarea **tareaP, Tarea **tareaR, int cant, char clave[]){

    if(tareaP!=NULL && tareaR!=NULL){

        for (int i=0; i<cant; i++)
        {
            if(tareaP[i]!=NULL && strstr(tareaP[i]->Descripcion, clave)!=NULL){

                return(tareaP[i]);

            }else if (tareaR[i]!=NULL && strstr(tareaR[i]->Descripcion, clave)!= NULL){

                return(tareaR[i]);
            }
        }
    }
    return(NULL);
}