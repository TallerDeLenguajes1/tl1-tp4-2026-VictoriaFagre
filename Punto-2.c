#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/* Implemente una funcionalidad que permita listar todas las tareas pendientes y realizadas.*/

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
Nodo *buscarTarea(Nodo *start, Nodo *tareaRealiz);
Nodo *quitarNodo(Nodo **start, int idQuitar);
Nodo *eliminarNodo(Nodo *nodoParaElim);
void insertarNodoEnLista(Nodo **start, Nodo *nuevoNodo);
void mostrarDatos(Tarea T);
void listarLista(Nodo *nodoAux);

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
            //quitarNodo(&start, id);
            Nodo *nodoParaQuitar = quitarNodo(&start, id);

            if (nodoParaQuitar != NULL){
                printf("Transfiriendo tarea: %s\n",nodoParaQuitar->T.Descripcion);
                insertarNodoEnLista(&tareaRealizada, nodoParaQuitar);
            }else{
                printf("No se encontro el ID %d en pendientes.\n",id);
            }
            
            printf("¿Quiere ingresar otro id?(si o no):");
            fgets(resp,10,stdin);
            resp[strcspn(resp, "\n")] = '\0';

        }while(strcmp("si",resp) == 0);
    }

    //listar tareas pendientes y realizadas:
    printf("Lista de tareas PENDIENTES:\n");
    listarLista(start);

    printf("Lista de tareas REALIZADAS:\n");
    listarLista(tareaRealizada);

    buscarTarea(start,tareaRealizada);
    
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

void listarLista(Nodo *nodoAux){
    while(nodoAux != NULL){
        mostrarDatos(nodoAux->T);
        nodoAux = nodoAux->Siguiente;
    }
}

Nodo *buscarTarea(Nodo *start, Nodo *tareaRealiz){
    char consul[10];
    printf("Buscar tarea por id o palabra?(ESCRIBIR: id o palabra):");
    fgets(consul,10,stdin);
    consul[strcspn(consul, "\n")] = '\0';

    int bandera = 0;

    if(strcmp("id",consul)==0){
        int id;
        printf("ID a consultar:");
        scanf("%d",&id);

        limpioBuffer();

        Nodo *aux1;
        aux1 = start;
        while(aux1 != NULL && aux1->T.TareaID != id){
             aux1 = aux1->Siguiente;
        }

        //aux1 da o el valor buscado o null 
        if(aux1 != NULL){
            printf("PENDIENTES: La tarea buscada es: %s",aux1->T.Descripcion);
            bandera = 1;
        }else{
            aux1 = tareaRealiz;
            while(aux1 != NULL && aux1->T.TareaID != id){
                aux1 = aux1->Siguiente;
            }
            if (aux1 != NULL){
                printf("REALIZADAS: La tarea buscada es: %s",aux1->T.Descripcion);
                bandera = 1;
            }
        }
    
    }else{

        printf("Palabra clave para buscar en descripción:");
        fgets(consul,10,stdin);
        consul[strcspn(consul, "\n")] = '\0'; //NO COMPARA BIEN strstr si no saco \0

        Nodo *aux2;
        aux2 = start;
        while(aux2 != NULL){
            if (strstr(aux2->T.Descripcion,consul) != NULL){
                printf("PENDIENTES:La tarea buscada es: %s.\n",aux2->T.Descripcion);
                bandera = 1;
            }
            aux2 = aux2->Siguiente;
        } 

        aux2 = tareaRealiz;
        while(aux2 != NULL){
            if(strstr(aux2->T.Descripcion,consul)!=NULL){
                printf("REALIZADAS:La tarea buscada es: %s.\n",aux2->T.Descripcion);
                bandera = 1;
            }
            aux2 = aux2->Siguiente;
        }
    }
    
    if(bandera != 0 && bandera != 1) printf("No hay tareas con esa palabra.\n");
}

void mostrarDatos(Tarea T){
    printf("ID: %d | Duracion: %d | Descripcion: %s\n", T.TareaID, T.Duracion, T.Descripcion);
}
