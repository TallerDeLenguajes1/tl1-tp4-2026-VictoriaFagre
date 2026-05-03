#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/* Implemente una interfaz para elegir qué tareas de la lista de pendientes deben ser transferidas 
a la lista de tareas realizadas.*/

typedef struct  Tarea{
    int TareaID;//numérico autoincremental comenzando en 1000
    char *Descripcion;
    int Duracion; //entre 10-100
}Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;


Tarea crearTarea();
Nodo *crearNodo(Tarea T);
Nodo *crearListaVacia();
Nodo *buscarNodo(Nodo *start, int IdBuscado); //idea: buscar el elemento a sacar
Nodo *quitarNodo(Nodo **start, int idQuitar);
Nodo *eliminarNodo(Nodo *nodoParaElim);
void insertarNodoEnLista(Nodo **start, Nodo *nuevoNodo);
void mostrarDatos(Tarea T);

void limpioBuffer();

int main(){

    srand(time(NULL));
    char resp[10]; //guardo 3 lugares porque con  2 solo me toma "s/0"
    Nodo *start = crearListaVacia(); // LISTA INICIALIZADA AFUERA
    //al puntero "start" se le suele poner "lista" de nombre tmb

    printf("Quiere agregar una tarea a la lista?(Responda: si o no):");
    fgets(resp,10,stdin);
    resp[strcspn(resp, "\n")] = '\0'; // Limpieza para strcmp
    
    while(strcmp("si",resp)==0){
        //no conviene hacer a tareaPend un puntero ya que el dato alojado es como una variable struct
        Tarea tareaPend = crearTarea();
        Nodo *nuevoNodo = crearNodo(tareaPend);
        insertarNodoEnLista(&start,nuevoNodo);

        /*creo cada nodo para que cargue una tarea, por lo tanto no sirve pasar la tarea en si, si no la tarea que esta
        contenida en dicho nodo*/
        printf("\n--- Tarea cargada correctamente ---\n");
        mostrarDatos(nuevoNodo->T);

        printf("\nAgrega OTRA tarea a la lista?(Responda: si o no): ");
        fgets(resp,10,stdin);
        resp[strcspn(resp, "\n")] = '\0';
    }
    
    Nodo *tareaRealizada = crearListaVacia();

    printf("Tiene para ingresar UN id de alguna tarea realizada?(si o no):");
    fgets(resp,10,stdin);
    resp[strcspn(resp, "\n")] = '\0';

    if(strcmp("si",resp) == 0){
        do{
            int id;
            printf("Ingrese el ID de la tarea que fue realizada:");
            scanf("%d",&id);

            limpioBuffer(); //siempre despues de un scanf y antes de fgets

            //Nodo *nodoEncontrado = buscarNodo(&start,id);
            //if(nodoEncontrado != NULL){
                Nodo *nodoParaQuitar = quitarNodo(&start, id);
                printf("Transfiriendo tarea: %s\n",nodoParaQuitar->T.Descripcion);
                insertarNodoEnLista(&tareaRealizada, nodoParaQuitar);
                eliminarNodo(nodoParaQuitar);

                if(eliminarNodo){
                    printf("El nodo %d fue quitado\n", id);
                }
            //}else{
            //     printf("ID %d no encontrado en pendientes.\n", id);
            //}
            
            printf("¿Quiere ingresar otro id?");
            fgets(resp,10,stdin);
            resp[strcspn(resp, "\n")] = '\0';

        }while(strcmp("si",resp) == 0);
    }
    
    return 0;
}

void limpioBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF){}
}

Tarea crearTarea(){
    //Genero id
    static int proximoID = 1000; // Mantiene el valor entre llamadas
    Tarea nuevaT;
    nuevaT.TareaID = proximoID++;

    //Descripción de la tarea
    char descripAux[500];
    printf("Ingrese la descripcion de la tarea:");
    fgets(descripAux,500,stdin);
    descripAux[strcspn(descripAux, "\n")] = '\0'; // Importante quitar el \n

    int cant = strlen(descripAux);

    nuevaT.Descripcion = (char*)malloc(cant*sizeof(char)+1);
    strcpy(nuevaT.Descripcion,descripAux);

    //Duración de la tarea
    nuevaT.Duracion = 10 + rand()%(100-10+1);
    return nuevaT;
}

Nodo *crearNodo(Tarea T){
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->T = T;
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}


Nodo *crearListaVacia(){
    return NULL;
}

void insertarNodoEnLista (Nodo **start, Nodo *nuevoNodo){
    nuevoNodo->Siguiente = *start;
    *start = nuevoNodo;
}

Nodo *buscarNodo(Nodo *start, int IdBuscado){
    Nodo *aux = start;
    while(aux != NULL &&aux->T.TareaID != IdBuscado){
        aux = aux->Siguiente;
    }
    return aux;
}

Nodo *quitarNodo(Nodo **start, int idQuitar){
    Nodo *nodoAux = (*start);
    Nodo *nodoAnt = NULL;

    while(nodoAux != NULL && nodoAux->T.TareaID != idQuitar){
        nodoAnt = nodoAux;
        nodoAux = nodoAux->Siguiente;
    }
    if (nodoAux != NULL){
        if (nodoAux == (*start)){
            (*start) = nodoAux->Siguiente;
        }else{
            nodoAnt->Siguiente = nodoAux->Siguiente;
        }

        nodoAux->Siguiente = NULL;
    }
    return (nodoAux);
}

Nodo *eliminarNodo(Nodo *nodoParaElim){
    if(nodoParaElim != NULL){
        free(nodoParaElim);
    }
}

void mostrarDatos(Tarea T){
    printf("ID: %d | Duracion: %d | Descripcion: %s\n", T.TareaID, T.Duracion, T.Descripcion);
}
