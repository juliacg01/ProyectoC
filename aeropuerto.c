#include "aeropuerto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TAM_PAIS 3
#define TAM_AERONAVE 10
#define TAM_NOMBRE 15
#define TAM_APELLIDO 25

void InicializarLista (Lista *lista){
	lista->inicioVuelo=NULL;
}

int ComprobarPais(char *Pais){
    if((strcmp(Pais, "ES")==0) || (strcmp(Pais, "IT")==0) || (strcmp(Pais, "AL")==0) || (strcmp(Pais, "RO")==0) || (strcmp(Pais, "FR")==0)){
        return 0;
    }
    else{
        printf("El pais introduccido es incorrecto \n");
        return 1;
    }
}

int ComprobarAeronave(char *Aeronave){
    if((strcmp(Aeronave, "biplano")==0) || (strcmp(Aeronave, "boeing")==0) || (strcmp(Aeronave, "aeroplano")==0)){
        return 0;
    }
    else{
        printf("La aeronave introduccido es incorrecto \n");
        return 1;
    }
}

int ComprobarAeropuerto (char *origen, char *destino){
    if(!(strcmp(origen, "ES")) != !(strcmp(destino, "ES"))){
        return 0;
    }
    else{
        printf("El origen o el destino del vuelo tiene que ser ES ya que es nuestro aeropuerto de referencia");
        return 1;
    }
}

int CompararFecha (Fecha fecha1, Fecha fecha2){
    //Comprueba año
    if (fecha1.anyo > fecha2.anyo){
        return 1;
    }
    else if (fecha1.anyo < fecha2.anyo){
        return 0;
    }
    else{
        //Si coincide el año mira el mes
        if (fecha1.mes > fecha2.mes){
            return 1;
        }
        else if (fecha1.mes < fecha2.mes){
            return 0;
        }
        else{
             //Si coincide el mes mira el dia
            if (fecha1.dia > fecha2.dia){
                return 1;
            }
            else if (fecha1.dia < fecha2.dia){
                return 0;
            }
            else{
                //Si coincide todda la fecha mira la hora
                if (fecha1.hora> fecha2.hora){
                    return 1;
                }
                else if (fecha1.hora < fecha2.hora){
                    return 0;
                }
                else{
                    //Si coincide todda la fecha mira la hora
                    if (fecha1.hora> fecha2.hora){
                        return 1;
                    }
                    else if (fecha1.hora < fecha2.hora){
                        return 0;
                    }
                    else{
                    //Si coindicen en fecha y hora no se realiza cambio
                    return 0;
                    }
                }
            }
        }
    }
}

void CrearNodoVuelo (Lista *lista, Vuelo *n_vuelo){
    Vuelo *nuevo_vuelo; 
    nuevo_vuelo = (Vuelo*)malloc(sizeof(Vuelo)); 
    
    nuevo_vuelo->ID = n_vuelo->ID;
    nuevo_vuelo->fecha.dia = n_vuelo->fecha.dia;
    nuevo_vuelo->fecha.mes = n_vuelo->fecha.mes;
    nuevo_vuelo->fecha.anyo = n_vuelo->fecha.anyo;
    nuevo_vuelo->fecha.hora = n_vuelo->fecha.hora;
    nuevo_vuelo->fecha.minuto = n_vuelo->fecha.minuto;
    nuevo_vuelo->origen = strdup(n_vuelo->origen);
    nuevo_vuelo->destino = strdup(n_vuelo->destino);
    nuevo_vuelo->aeronave = strdup(n_vuelo->aeronave);
    nuevo_vuelo->asientos_total = n_vuelo->asientos_total;
    nuevo_vuelo->siguiente = NULL;
    
    if(lista->inicioVuelo == NULL){
        lista->inicioVuelo = nuevo_vuelo;
        lista->tamanyo++;
    }
    else{
        //Si ya hay datos guardados crearemos un nuevo vuelo 
        Vuelo* aux;
        aux = lista->inicioVuelo;
        //Se comprueba la lista hasta que ya no haya mas vuelos guardados para crear uno nuevo 
        while (aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        //Al llegar al final, crea un nuevo vuelo en el puntero "siguiente" que antes apuntaba a NULL
        aux -> siguiente = nuevo_vuelo;
        lista->tamanyo++;
    }
}

void LeerFichero (Lista *lista, FILE *salida, FILE *llegada){
    Vuelo *nuevo_vuelo; 
    nuevo_vuelo = (Vuelo*)malloc(sizeof(Vuelo));
    nuevo_vuelo->origen = (char *)malloc(sizeof(char)*TAM_PAIS);
    nuevo_vuelo->destino = (char *)malloc(sizeof(char)*TAM_PAIS);
    nuevo_vuelo->aeronave = (char *)malloc(sizeof(char)*TAM_AERONAVE);

    while (!feof(salida)){
        //Acordarme de poner el formato en el fscanf, porque si no mi novio me pega con el pene en el ojo
        fscanf (salida, "%d %d %d %d %d %d %s %s %s %d", 
        &nuevo_vuelo->ID, 
        &nuevo_vuelo->fecha.dia, 
        &nuevo_vuelo->fecha.mes, 
        &nuevo_vuelo->fecha.anyo, 
        &nuevo_vuelo->fecha.hora, 
        &nuevo_vuelo->fecha.minuto, 
        nuevo_vuelo->origen, 
        nuevo_vuelo->destino, 
        nuevo_vuelo->aeronave,
        &nuevo_vuelo->asientos_total)!=EOF; 

        CrearNodoVuelo(lista, nuevo_vuelo);
    };

    while (!feof(llegada)){
        fscanf (llegada, "%d %d %d %d %d %d %s %s %s %d", 
        &nuevo_vuelo->ID, 
        &nuevo_vuelo->fecha.dia, 
        &nuevo_vuelo->fecha.mes, 
        &nuevo_vuelo->fecha.anyo, 
        &nuevo_vuelo->fecha.hora, 
        &nuevo_vuelo->fecha.minuto, 
        nuevo_vuelo->origen, 
        nuevo_vuelo->destino, 
        nuevo_vuelo->aeronave,
        &nuevo_vuelo->asientos_total)!=EOF; 

        CrearNodoVuelo(lista, nuevo_vuelo);
    };

    free(nuevo_vuelo);
}

void EscribirFicheros (Lista *lista, FILE *salida, FILE *llegada){
    Vuelo *punteroVuelos; 
    punteroVuelos = lista->inicioVuelo;

    while(punteroVuelos != NULL){
        if(strcmp(punteroVuelos->origen, "ES")){
            fprintf(salida, "%d %d %d %d %d %d %s %s %s %d\n", 
            punteroVuelos->ID, 
            punteroVuelos->fecha.dia, 
            punteroVuelos->fecha.mes, 
            punteroVuelos->fecha.anyo, 
            punteroVuelos->fecha.hora, 
            punteroVuelos->fecha.minuto, 
            punteroVuelos->origen, 
            punteroVuelos->destino, 
            punteroVuelos->aeronave, 
            punteroVuelos->asientos_total);
        }
        if (strcmp(punteroVuelos->destino, "ES")){
            fprintf(llegada, "%d %d %d %d %d %d %s %s %s %d\n", 
            punteroVuelos->ID, 
            punteroVuelos->fecha.dia, 
            punteroVuelos->fecha.mes, 
            punteroVuelos->fecha.anyo, 
            punteroVuelos->fecha.hora, 
            punteroVuelos->fecha.minuto, 
            punteroVuelos->origen, 
            punteroVuelos->destino, 
            punteroVuelos->aeronave, 
            punteroVuelos->asientos_total);
        }
        punteroVuelos= punteroVuelos->siguiente;
    }
}

void InsertarDatosVuelo(Vuelo *nuevo_vuelo){
    nuevo_vuelo->inicioPasajeros = NULL;
    nuevo_vuelo->asientos_ocup = 0;

    //Introducir los datos del vuelo
    printf("\n");
    printf("Inserta el ID del nuevo vuelo: ");
    scanf("%d", &nuevo_vuelo->ID);

    printf ("Introduce el dia del vuelo: ");
    scanf("%d", &nuevo_vuelo->fecha.dia);

    printf("Introduce el mes del vuelo: ");
    scanf("%d", &nuevo_vuelo->fecha.mes);

    printf("Introduce el año del vuelo: ");
    scanf("%d", &nuevo_vuelo->fecha.anyo);

    printf("Introduce la hora  de llegada o salida del vuelo: ");
    scanf("%d", &nuevo_vuelo->fecha.hora);

    printf("Introduce el minuto de llegada o salida del vuelo: ");
    scanf("%d", &nuevo_vuelo->fecha.minuto);

    do{
        printf("\n");
        do{
            printf("Insertar el código del país de origen: (ES, IT, AL, RO, FR): ");
            nuevo_vuelo->origen = (char *)malloc(sizeof(char)*TAM_PAIS);
            scanf("%s", nuevo_vuelo->origen);
        }while(ComprobarPais(nuevo_vuelo->origen)==1);

        do{
            printf("Insertar el código del país de destino: (ES, IT, AL, RO, FR): ");
            nuevo_vuelo->destino = (char *)malloc(sizeof(char)*TAM_PAIS);
            scanf("%s", nuevo_vuelo->destino);
        }while(ComprobarPais(nuevo_vuelo->destino)==1);
    }while(ComprobarAeropuerto(nuevo_vuelo->origen, nuevo_vuelo->destino) == 1);

    do{
        printf("Insertar el tipo de aeronave: (biplano, boeing, aeroplano): ");
        nuevo_vuelo->aeronave = (char *)malloc(sizeof(char)*TAM_AERONAVE);
        scanf("%s", nuevo_vuelo->aeronave);
    }while(ComprobarAeronave(nuevo_vuelo->aeronave)==1);

    if (strcmp(nuevo_vuelo->aeronave, "biplano")==0){
        nuevo_vuelo->asientos_total= 2;
    }
    else if (strcmp(nuevo_vuelo->aeronave, "boeing")==0){
        nuevo_vuelo->asientos_total = 10;
    }
    else{
        nuevo_vuelo->asientos_total = 5;
    }
}

void InsertarVuelo (Lista *lista) {
    Vuelo *nuevo_vuelo; //Crea un nuevo vuelo
    nuevo_vuelo = (Vuelo*)malloc(sizeof(Vuelo)); //Reserva memoria para los datos del nuevo vuelo

    InsertarDatosVuelo(nuevo_vuelo);

    //Cuando finalizamos de introduccir todos los valores señalamos al siguiente vuelo como NULL
    nuevo_vuelo->siguiente = NULL;

    if(lista->inicioVuelo == NULL){
        lista->inicioVuelo = nuevo_vuelo;
        lista->tamanyo++;
    }
    else{
        //Si ya hay datos guardados crearemos un nuevo vuelo 
        /*Cuando apuntemos al siguiente vuelo sobre escribiremos en la lista
            para ello necisitamos guardar los vuelos y trabajar sobre una variable auxiliar */
        Vuelo* aux;
        aux = lista->inicioVuelo;
        //Se comprueba la lista hasta que ya no haya mas vuelos guardados para crear uno nuevo 
        while (aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        //Al llegar al final, crea un nuevo vuelo en el puntero "siguiente" que antes apuntaba a NULL
        aux -> siguiente = nuevo_vuelo;
        lista->tamanyo++;
    }

} 

Vuelo *EncontrarIDVuelo(Lista *lista, int ID){
    Vuelo *punteroVuelos;
    punteroVuelos=lista->inicioVuelo;

    while (punteroVuelos != NULL ){
        if (punteroVuelos->ID == ID ){
            break;
        }
        else{
            punteroVuelos = punteroVuelos->siguiente;
        }
    }
    return punteroVuelos;
}

void InsertarDatosPasajero(Vuelo* punteroVuelos, Pasajeros *nuevo_pasajero){
    //Introducir los datos del pasajero
    printf("\n");

    //Asignamos el siguiente asiento libre al pasajero
    nuevo_pasajero->asiento_asig = punteroVuelos->asientos_ocup + 1;
    punteroVuelos->asientos_ocup ++;

    printf("Introduce el nombre del pasajero: ");
    nuevo_pasajero->nombre = (char *)malloc(sizeof(char)*TAM_NOMBRE);
    scanf("%s", nuevo_pasajero->nombre);

    printf("Introduce el apellido del pasajero: ");
    nuevo_pasajero->apellido = (char *)malloc(sizeof(char)*TAM_APELLIDO);
    scanf("%s", nuevo_pasajero->apellido);

    printf("Introduce el DNI del pasajero:");
    scanf("%d", &nuevo_pasajero->DNI);

    //Marcamos que el destino del pasajero sea el mismo que el del vuelo seleccionado
    nuevo_pasajero->destino = punteroVuelos->destino;

}

void InsertarPasajeros (Lista *lista, int ID){
    //Primero comprobamos la ID que introduce el usuario 
    Vuelo *punteroVuelos;
    punteroVuelos = EncontrarIDVuelo(lista, ID);

    //Si hay un vuelo con dicha ID crearemos la lista de pasajeros para dicho vuelo
    if(punteroVuelos!=NULL && punteroVuelos->asientos_ocup < punteroVuelos->asientos_total){
        Pasajeros* nuevo_pasajero;
        nuevo_pasajero = (Pasajeros*)malloc(sizeof(Pasajeros));
        nuevo_pasajero->siguiente = NULL;
        InsertarDatosPasajero(punteroVuelos, nuevo_pasajero);

        if(punteroVuelos->inicioPasajeros == NULL){
            punteroVuelos->inicioPasajeros = nuevo_pasajero;
        }
        else{
            Pasajeros* aux;
            aux = punteroVuelos->inicioPasajeros;
            //Se comprueba la lista hasta que ya no haya mas vuelos guardados para crear uno nuevo 
            while (aux->siguiente != NULL){
                aux = aux->siguiente;
            }
            //Al llegar al final, crea un nuevo vuelo en el puntero "siguiente" que antes apuntaba a NULL
            aux -> siguiente = nuevo_pasajero;
        }
    }
    //Comprobamos si hay espacio en el vuelo
    else if (punteroVuelos!=NULL && punteroVuelos->asientos_ocup == punteroVuelos->asientos_total){
        printf("El vuelo seleccionado esta completo \n");
    }
    //si no se encuentra guardada la ID introducida se le avisa al usuario
    else{
        printf("No se ha encontrado el vuelo con la ID introduccida \n");
    }

}

void MostrarDatos(Lista *lista) {
	Vuelo* punteroVuelos;
    Pasajeros* punteroPasajeros;
    
	punteroVuelos=lista->inicioVuelo;
    punteroPasajeros=punteroVuelos->inicioPasajeros;

	while (punteroVuelos != NULL){
        printf("ID: %d Fecha: %d/%d/%d Hora: %d:%d Origen: %s Destino %s Aeronave: %s Asientos: %d\n", 
        punteroVuelos->ID, 
        punteroVuelos->fecha.dia, 
        punteroVuelos->fecha.mes, 
        punteroVuelos->fecha.anyo, 
        punteroVuelos->fecha.hora, 
        punteroVuelos->fecha.minuto, 
        punteroVuelos->origen, 
        punteroVuelos->destino, 
        punteroVuelos->aeronave, 
        punteroVuelos->asientos_total);
            
        printf("\t Pasajeros que se encuentran en el vuelo: \n");
        if(punteroVuelos->inicioPasajeros != NULL){
            while (punteroPasajeros != NULL){

                printf(" \t Nombre: %s Apellido: %s DNI: %d Destino: %s Asiento asignado: %d\n",
                punteroPasajeros->nombre, punteroPasajeros->apellido, punteroPasajeros->DNI, punteroPasajeros->destino, punteroPasajeros->asiento_asig);
                
                punteroPasajeros=punteroPasajeros->siguiente;
            }
        }
        punteroVuelos= punteroVuelos->siguiente;
        // Si se ha recorrido todos los pasajeros y pasas al siguiente vuelo, el punteroPasajeros tiene que señalar al primer pasajero del siguiente vuelo
        if(punteroVuelos != NULL){
            punteroPasajeros= punteroVuelos->inicioPasajeros;
        }
	}
    printf("\n");
}

void BuscarVuelos (Lista *lista, int ID){
    Vuelo *punteroVuelos;
    punteroVuelos = EncontrarIDVuelo(lista, ID);

    if(punteroVuelos!=NULL){
        Pasajeros* punteroPasajeros;
        punteroPasajeros=punteroVuelos->inicioPasajeros;
        
        printf("Los datos del vuelo buscado son: \n");
        printf("ID: %d Fecha: %d/%d/%d Hora: %d:%d Origen: %s Destino %s Aeronave: %s Asientos: %d \n",
        punteroVuelos->ID, punteroVuelos->fecha.dia, punteroVuelos->fecha.mes, punteroVuelos->fecha.anyo, punteroVuelos->fecha.hora, punteroVuelos->fecha.minuto, punteroVuelos->origen, punteroVuelos->destino, punteroVuelos->aeronave, punteroVuelos->asientos_total);
        while (punteroPasajeros != NULL){
            printf(" \t Nombre: %s Apellido: %s DNI: %d Destino: %s Asiento asignado: %d\n",
            punteroPasajeros->nombre, punteroPasajeros->apellido, punteroPasajeros->DNI, punteroPasajeros->destino, punteroPasajeros->asiento_asig);
            punteroPasajeros=punteroPasajeros->siguiente;
        }
    }
    else{
        printf("No se ha encontrado el vuelo con la ID introduccida \n");
    }
}

void EliminarVuelo (Lista *lista ,int ID) {
    Vuelo *punteroVuelos;
    Vuelo *borrador;
    punteroVuelos = lista->inicioVuelo;

    //Comprobamos todos los vuelos guardados
    while (punteroVuelos != NULL ){
        //PRIMER CASO: Eliminar el primer nodo
        //Señalamos el segundo nodo como el inicio de la lista y eliminamos el primero
        if (lista->inicioVuelo->ID == ID){
            lista->inicioVuelo = punteroVuelos->siguiente;
            //Hacemos free de todos los malloc que creamos para añadir datos, y poor ultimo, un free para eliminar el nodo por completo
            free(punteroVuelos->origen);
            free(punteroVuelos->destino);
            free(punteroVuelos->aeronave);
            free(punteroVuelos);
            printf("Se ha eliminado el vuelo correctamente \n");
            break;
        }
        //SEGUNDO CASO: Eliminar el ultimo nodo
        if (punteroVuelos->ID == ID && punteroVuelos->siguiente == NULL){
            borrador->siguiente = NULL;
            free(punteroVuelos->origen);
            free(punteroVuelos->destino);
            free(punteroVuelos->aeronave);
            free(punteroVuelos);
            printf("Se ha eliminado el vuelo correctamente\n");
            break;
        }
        //TERCER CASO: Eliminar nodo del medio
        else if(punteroVuelos->ID == ID){
            borrador->siguiente = punteroVuelos->siguiente;
            free(punteroVuelos->origen);
            free(punteroVuelos->destino);
            free(punteroVuelos->aeronave);
            free(punteroVuelos);
            printf("Se ha eliminado el vuelo correctamente \n");
            break;
        }
        //Si el vuelo no coincide con la ID introducida se pasa al siguiente vuelo
        else{
            //Creamos un puntero que vaya una lista por dentras del puntero principal
            borrador=punteroVuelos;
            punteroVuelos = punteroVuelos->siguiente;
        }
    }

    //Si acabamos de comprobar todos los vuelos sin ninguna coincidencia informamos al usuario
    if (punteroVuelos == NULL){
        printf("No se ha encontrado el vuelo con la ID introduccida \n");
    }         
}

void BuscarPasajero (Lista *lista, int DNI){
    Vuelo *punteroVuelos;
    punteroVuelos = lista->inicioVuelo;
    Pasajeros *punteroPasajeros;
    punteroPasajeros = punteroVuelos->inicioPasajeros;
    int Salir= 0;

    while (punteroVuelos != NULL){

        while (punteroPasajeros!= NULL){
            //Si encontramos uno con el mismo ID mostramos sus datos
            if (punteroPasajeros->DNI == DNI ){
                printf("Nombre: %s Apellido: %s DNI: %d Destino: %s Asiento asignado: %d\n",
                punteroPasajeros->nombre, 
				punteroPasajeros->apellido, 
				punteroPasajeros->DNI, 
				punteroPasajeros->destino, 
				punteroPasajeros->asiento_asig);
                Salir = 1;
                break;
            }
            else{
                punteroPasajeros = punteroPasajeros->siguiente;
            }
        }
        
        if (Salir == 1){
            break;
        }
        // Si encuentra el pasajero, se debe dejar de recorrer los vuelos
        if(punteroPasajeros != NULL){
            break;
        }

        punteroVuelos = punteroVuelos->siguiente;
        if(punteroVuelos != NULL){
            punteroPasajeros= punteroVuelos->inicioPasajeros;
        }
    }

    if (punteroPasajeros == NULL){
        printf("No se ha encontrado el pasajero con el DNI introduccido. ");
    }
}

void EliminarPasajero (Lista *lista, int DNI){
    Vuelo *punteroVuelos;
    punteroVuelos = lista->inicioVuelo;
    Pasajeros *punteroPasajeros;
    Pasajeros *borrador;
    punteroPasajeros = punteroVuelos->inicioPasajeros;
    int Eliminado = 0;

    //Recorremos todos los vuelos
    while (punteroVuelos!= NULL ){
        //Y dentro de cada vuelo recorremos todos los pasajeros
        while(punteroPasajeros != NULL){
            //PRIMER CASO: Eliminar el primer nodo
            if (punteroVuelos->inicioPasajeros->DNI == DNI){
                punteroVuelos->inicioPasajeros = punteroPasajeros->siguiente;
                //Hacemos free de todos los malloc que creamos para añadir datos, y por ultimo, un free para eliminar el nodo por completo
                free(punteroPasajeros->nombre);
                free(punteroPasajeros->apellido);
                free(punteroPasajeros);
                printf("Se ha eliminado el pasajero correctamente \n");
                Eliminado = 1;
                break;
            }
            //SEGUNDO CASO: Eliminar el ultimo nodo
            if (punteroPasajeros->DNI == DNI && punteroPasajeros->siguiente == NULL){
                borrador->siguiente = NULL;
                free(punteroPasajeros->nombre);
                free(punteroPasajeros->apellido);
                free(punteroPasajeros);
                printf("Se ha eliminado el pasajero correctamente \n");
                Eliminado = 1;
                break;
            }
            //TERCER CASO: Eliminar nodo del medio
            if(punteroPasajeros->DNI == DNI){
                borrador->siguiente = punteroPasajeros->siguiente;
                free(punteroPasajeros->nombre);
                free(punteroPasajeros->apellido);
                free(punteroPasajeros);
                printf("Se ha eliminado el pasajero correctamente \n");
                Eliminado = 1;
                break;
            }
            else{
                borrador=punteroPasajeros;
                punteroPasajeros = punteroPasajeros->siguiente;
            }
        }

        // Si se ha eliminado, debe dejar de recorrer los vuelos
        if(Eliminado == 1){
            break;
        }

        punteroVuelos = punteroVuelos->siguiente;
        if(punteroVuelos != NULL){
            punteroPasajeros= punteroVuelos->inicioPasajeros;
        }
        
    }

    if (Eliminado == 0){
        printf("No se ha encontrado el pasajero con el DNI introduccido.");
    }
}


void VaciarLista (Lista *lista){
    Vuelo *punteroVuelos;
    Pasajeros *punteroPasajeros;
    punteroVuelos = lista->inicioVuelo;
    punteroPasajeros = punteroVuelos->inicioPasajeros;

    Pasajeros *auxPasajeros;
    Vuelo *auxVuelo;

    while (punteroVuelos != NULL){
        while (punteroPasajeros != NULL){
            auxPasajeros = punteroPasajeros;
            punteroPasajeros = punteroPasajeros->siguiente;
            free(auxPasajeros->nombre);
            free(auxPasajeros->apellido);
            free(auxPasajeros);
        }
        
        if(punteroVuelos != NULL){
            punteroPasajeros= punteroVuelos->inicioPasajeros;
        }
        auxVuelo = punteroVuelos;
        punteroVuelos=punteroVuelos->siguiente;
        free(auxVuelo->origen);
        free(auxVuelo->destino);
        free(auxVuelo->aeronave);
        free(auxVuelo);
    }
}

void OrdenarVuelos (Lista *lista) {
    Vuelo *pActual;
    Vuelo *pAnterior;
    Vuelo *pSiguiente;
    int DetectorCambio = 0;

    if(lista->inicioVuelo == NULL){
        return;
    }

    pActual = lista->inicioVuelo;
    if(pActual->siguiente == NULL){
        return;
    }
    
    while (pActual != NULL){
        pSiguiente = pActual->siguiente;
        //Cuando se comprueban los dos primeros valores
        if (pSiguiente != NULL && pActual == lista->inicioVuelo && CompararFecha(pActual->fecha, pSiguiente->fecha) == 1){
            lista->inicioVuelo = pActual->siguiente;
            pActual->siguiente = pSiguiente->siguiente;
            pSiguiente->siguiente = pActual;
            //Una vez realizado el cambio se vuelve a colocar los punteros en su posicion correcta
            pActual = lista->inicioVuelo->siguiente;
            pSiguiente = pActual->siguiente;
            DetectorCambio = 1;
        }
        else if (pSiguiente != NULL && CompararFecha(pActual->fecha, pSiguiente->fecha) == 1){
            pAnterior->siguiente = pActual->siguiente;
            pActual->siguiente = pSiguiente->siguiente;
            pSiguiente->siguiente = pActual;
            //Una vez realizado el cambio se vuelve a colocar los punteros en su posicion correcta
            pActual = pAnterior->siguiente;
            pSiguiente = pActual->siguiente;
            DetectorCambio = 1;
        }
        pAnterior = pActual;
        pActual = pActual->siguiente;
    }

    if(DetectorCambio==1){
        OrdenarVuelos(lista);
    }
}










