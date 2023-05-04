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
Nodo* buscarTareaId(Nodo *tarea, int id);
Nodo* quitarNodo(Nodo **cabecera, int id);
void mostrarTarea(Tarea t);
void mostrarTareas(Nodo *t);
void mostrarDatos(Nodo *lista);
void borrarUnNodo(Nodo * nodo);
void eliminarNodo(Nodo **cabecera, int id);
void insertarNodo(Nodo **cabecera, int id, char *descrip, int duracion);
void insertarNodo2(Nodo **cabecera, Nodo *nuevoNodo);


//PROGRAMA PRINCIPAL
int main(){

    int resp, cont=1, id=1, duracion, id2, aux;
    char buff[tama], buff2[tama], *clave;

    Nodo *tareasPendientes;
    Nodo *tareasRealizadas;
    Nodo *tareasEnProceso;
    Nodo *tareaEncontrada; 

    tareasPendientes=crearListaVacia();
    tareasRealizadas=crearListaVacia();
    tareasEnProceso=crearListaVacia();

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
            printf("\nTarea Pendiente=(1)\nTarea Realizada=(2)\nTarea en Proceso=(3)\n");
            printf("Seleccionar: ");
            scanf("%d", &resp);

        } while (resp!=1 && resp!=2 && resp!=3);

        if(resp==2){

            insertarNodo(&tareasRealizadas, nodoaux->T.TareaID, nodoaux->T.Descripcion, nodoaux->T.Duracion);
            nodoAnterior=nodoaux;
            nodoaux=nodoaux->Siguiente;
            eliminarNodo(&tareasPendientes, nodoAnterior->T.TareaID);

        }else if(resp==3){

            insertarNodo(&tareasEnProceso, nodoaux->T.TareaID, nodoaux->T.Descripcion, nodoaux->T.Duracion);
            nodoAnterior=nodoaux;
            nodoaux=nodoaux->Siguiente;
            eliminarNodo(&tareasPendientes, nodoAnterior->T.TareaID);

        }else{
            nodoaux=nodoaux->Siguiente;
        }
    }

    do
    {
        printf("\n-----TAREAS PENDIENTES-----\n");
        mostrarTareas(tareasPendientes);

        printf("\n-----TAREAS REALIZADAS-----\n");
        mostrarTareas(tareasRealizadas);

        printf("\n-----TAREAS EN PROCESO-----\n");
        mostrarTareas(tareasEnProceso);

        fflush(stdin);
        printf("\nSeleccione una Tarea por ID: ");
        scanf("%d", &id2);

        Nodo *nodoaux2;

        do
        {
            printf("\n1-Mover a Tareas Pendientes\n");
            printf("2-Mover a Tareas Realizadas\n");
            printf("3-Mover a Tareas En Proceso\n");
            printf("4-Eliminar Tarea\n");
            printf("5-Cancelar Operacion\n");
            printf("Operacion a Realizar: ");
            scanf("%d", &aux);

            tareaEncontrada=buscarTareaId(tareasPendientes, id2);
            
            if(tareaEncontrada==NULL)
            {
                tareaEncontrada=buscarTareaId(tareasRealizadas, id2);
                if(tareaEncontrada==NULL)
                {
                    tareaEncontrada=buscarTareaId(tareasEnProceso, id2);
                    if(tareaEncontrada==NULL)
                    {
                        printf("\nNO SE ENCONTRO LA TAREA");
                    }else{
                        nodoaux2=quitarNodo(&tareasEnProceso, id2);
                    }

                }else{
                    nodoaux2=quitarNodo(&tareasRealizadas, id2);
                }

            }else{
                nodoaux2=quitarNodo(&tareasPendientes, id2);
            }

            switch (aux)
            {
            case 1:
            insertarNodo2(&tareasPendientes, nodoaux2);
            aux=5;
            break;
            case 2:
            insertarNodo2(&tareasRealizadas, nodoaux2);
            aux=5;
            break;
            case 3:
            insertarNodo2(&tareasEnProceso, nodoaux2);
            aux=5;
            break;
            case 4:
            borrarUnNodo(nodoaux2);
            aux=5;
            break;
            default:
            break;
            }

            
        } while (aux!=5);

        printf("\nModificar otra tarea (Si=1), (No=0)\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &aux);

    } while (aux!=0);

    printf("\n-----TAREAS PENDIENTES-----\n");
    mostrarTareas(tareasPendientes);
    mostrarDatos(tareasPendientes);

    printf("\n-----TAREAS REALIZADAS-----\n");
    mostrarTareas(tareasRealizadas);
    mostrarDatos(tareasRealizadas);

    printf("\n-----TAREAS EN PROCESO-----\n");
    mostrarTareas(tareasEnProceso);
    mostrarDatos(tareasEnProceso);

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

//Otra forma de Insercion de nodo

void insertarNodo2(Nodo **cabecera, Nodo *nuevoNodo){

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

//FUncion para Borrar un Nodo

void borrarUnNodo(Nodo * nodo){
    if (nodo != NULL)
    {
    free(nodo->T.Descripcion);
    free(nodo);    
    }
}

//Funcion para Quitar un Nodo de una Lista y retornarlo

Nodo* quitarNodo(Nodo**cabecera, int id){

    Nodo *aux=*cabecera;
    Nodo *auxAnterior=NULL;

    while(aux && aux->T.TareaID!=id){

        auxAnterior=aux;
        aux=aux->Siguiente;
    }

    if(aux!=NULL)
    {
        if(*cabecera==aux){
            *cabecera=aux->Siguiente;
            return aux;
        }else{
            auxAnterior->Siguiente=aux->Siguiente;
            return aux;
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

Nodo* buscarTareaId(Nodo *tarea, int id){

    Nodo *aux=tarea;

    while(aux!=NULL && aux->T.TareaID!=id){

        aux=aux->Siguiente;
    }
    return aux;
}

//Funcion para Mostrar la Cantidad de Tareas y el tiempo asociado de la lista

void mostrarDatos(Nodo *lista){

    Nodo *aux=lista;
    int cantTareas=0, duracion=0;

    while(aux!=NULL){

        cantTareas++;
        duracion=duracion+aux->T.Duracion;
        aux=aux->Siguiente;
    }

    printf("\nCantidad de Tareas: %d\n", cantTareas);
    printf("Duracion total: %d", duracion);
}
