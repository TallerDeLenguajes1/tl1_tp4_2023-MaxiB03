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

typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;

Nodo* crearListaVacia();
Nodo* crearNodo(int id, char descrip[], int duracion);
void insertarNodo(Nodo **cabecera, int id, char *descrip, int duracion);
void eliminarNodo(Nodo **cabecera, int id);
void mostrarTarea(Tarea t);
void mostrarTareas(Nodo *t);
Nodo* buscarTareaId(Nodo *tareaP, Nodo *tareaR, int id);
Nodo* buscarTareaPorClave(Nodo *tareaP, Nodo *tareaR, char clave[]);

//Programa Principal

int main(){

    int resp, cont=1, id=1, duracion, id2;
    char buff[tama], buff2[tama], *clave;

    Nodo *tareasPendientes;
    Nodo *tareasRealizadas;
    Nodo *tareaEncontrada;

    tareasPendientes=crearListaVacia();
    tareasRealizadas=crearListaVacia();

    do
    {
        printf("\n--------CARGAR TAREA[%d]--------\n", cont++);

        fflush(stdin);
        printf("Ingrese la Descripcion: ");
        gets(buff);

        fflush(stdin);
        printf("Ingrese Duracion de la Tarea: ");
        scanf("%d", &duracion);

        insertarNodo(&tareasPendientes, id, buff, duracion);

        id++;

        fflush(stdin);
        printf("Finalizar Carga de Tareas? (Si=1), (No=0): ");
        scanf("%d", &resp);

    } while (resp!=1);

    Nodo *nodoaux;
    Nodo *nodoAnterior;
    nodoaux=tareasPendientes;

    while(nodoaux != NULL){

        printf("\n-------- TAREA[%d] --------\n",nodoaux->T.TareaID);
        mostrarTarea(nodoaux->T);

        do
        {
            fflush(stdin);
            printf("\nRealizo la Tarea? (Si=1), (No=0): ");
            scanf("%d", &resp);

        } while (resp!=1 && resp!=0);

        if(resp==1){

            insertarNodo(&tareasRealizadas, nodoaux->T.TareaID, nodoaux->T.Descripcion, nodoaux->T.Duracion);
            nodoAnterior=nodoaux;
            nodoaux=nodoaux->Siguiente;
            eliminarNodo(&tareasPendientes, nodoAnterior->T.TareaID);

        }else{
            nodoaux=nodoaux->Siguiente;
        }
    }

    printf("\n-----TAREAS PENDIENTES-----\n");
    mostrarTareas(tareasPendientes);

    printf("\n-----TAREAS REALIZADAS-----\n");
    mostrarTareas(tareasRealizadas);
    
    fflush(stdin);
    printf("\nBuscar Tarea, Ingrese un ID: ");
    scanf("%d", &id2);

    tareaEncontrada=buscarTareaId(tareasPendientes, tareasRealizadas, id2);

    if(tareaEncontrada != NULL){

        printf("\n-----TAREA ENCONTRADA-----\n");
        mostrarTarea(tareaEncontrada->T);

    }else{
        printf("\n-----NO SE ENCONTRO LA TAREA -----\n");
    }

    fflush(stdin);
    printf("\nBuscar Tarea, Ingrese palabra clave: ");
    gets(buff2);
    clave=(char*)malloc(sizeof(char)* (strlen(buff2)+1) );
    strcpy(clave,buff2);

    tareaEncontrada=buscarTareaPorClave(tareasPendientes, tareasRealizadas, clave);

    if(tareaEncontrada != NULL){

        printf("\n-----TAREA ENCONTRADA-----\n");
        mostrarTarea(tareaEncontrada->T);

    }else{
        printf("\n-----NO SE ENCONTRO LA TAREA -----\n");
    }

    return 0;
}



//Funcion para Crear la lista

Nodo* crearListaVacia(){
    return NULL;
}

//Funcion para Crear un Nodo

Nodo* crearNodo(int id, char descrip[], int duracion){

    Nodo *nuevoNodo=(Nodo*)malloc(sizeof(Nodo));

    nuevoNodo->T.Descripcion=(char *) malloc(sizeof(char) * strlen(descrip) + 1);
    strcpy(nuevoNodo->T.Descripcion, descrip);

    nuevoNodo->T.TareaID=id;
    nuevoNodo->T.Duracion=duracion;

    return nuevoNodo;
}

//Funcion para Insertar un Nodo en la Lista

void insertarNodo(Nodo **cabecera, int id, char *descrip, int duracion){

    Nodo *nuevoNodo=crearNodo(id, descrip, duracion);

    nuevoNodo->Siguiente=*cabecera;
    *cabecera=nuevoNodo;
}

//Funcion para eliminar Nodo de la lista

void eliminarNodo(Nodo **cabecera, int id){

    Nodo *aux=*cabecera;
    Nodo *auxAnterior=NULL;

    while(aux!=NULL && aux->T.TareaID!=id){

        auxAnterior=aux;
        aux=aux->Siguiente;
    }

    if(aux==NULL){ //Significa que no se encontro el nodo con ese dato o la lista esta vacia

        if(*cabecera==NULL){
            printf("\nLa Lista esta Vacia");
        }else{
            printf("\nNo se encontro el elemento");
        }

    }else{

        if(*cabecera==aux){  //Significa que quiero borrar el primer elemento
            *cabecera=aux->Siguiente;
        }else{
            auxAnterior->Siguiente=aux->Siguiente;
            free(aux->T.Descripcion);
            free(aux);
        }
    }
}

//Funcion para Mostrar la Tarea

void mostrarTarea(Tarea t){

    printf("ID Tarea: %d\n", t.TareaID);
    printf("Descripcion: %s\n", t.Descripcion);
    printf("Duracion: %d\n", t.Duracion);

}

//Funcion para Mostrar todas las Tareas

void mostrarTareas(Nodo *t){

    Nodo *aux=t;
  
    while(aux != NULL){

        printf("\n-------- TAREA[%d] --------\n",aux->T.TareaID);
        mostrarTarea(aux->T);
        aux=aux->Siguiente;
    }
}

//Funcion para buscar una tarea por ID

Nodo* buscarTareaId(Nodo *tareaP, Nodo *tareaR, int id){

    Nodo *aux=tareaP;

    while(aux!=NULL && aux->T.TareaID!=id){

        aux=aux->Siguiente;
    }

    if(aux==NULL){

        aux=tareaR;

        while(aux!=NULL && aux->T.TareaID!=id){
            aux=aux->Siguiente;
        }
    }
    return aux;
}

//Funcion para buscar una tarea por Palabra Clave

Nodo* buscarTareaPorClave(Nodo *tareaP, Nodo *tareaR, char clave[]){

    Nodo *aux=tareaP;

    while (aux && strstr(aux->T.Descripcion, clave) == NULL)
    {
        aux =aux->Siguiente;
    }
    if (aux == NULL)
    {
        aux = tareaR;
        while (aux && strstr(aux->T.Descripcion, clave) == NULL)
        {
            aux =aux->Siguiente;
        }
    }
    return aux;
}