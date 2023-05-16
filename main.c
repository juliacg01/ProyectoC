#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeropuerto.h"

void menu (){
    printf ("1. Insertar un nuevo vuelo de entrada o salida\n");
    printf ("2. Insertar un nuevo pasajero\n");
    printf ("3. Eliminar un vuelo \n");
    printf("4. Eliminar un pasajero\n");
    printf("5. Mostrar la lista de vuelos de salida o entrada\n");
    printf("6. Ordenar vuelos\n");
    printf("7. Buscar vuelo \n");
    printf ("8. Buscar pasajero\n");
    printf ("9. Salir del programa \n");
    printf ("Seleccione el numero de la operación que deseas realizar: ");
}

int main(int argc, char *argv[]){
    int opcion, ID, DNI;
    FILE *salida, *llegada;

    Lista *lista = (Lista*)malloc(sizeof(Lista));

    llegada = fopen (argv[1], "r"); //Lo abrimos en modo lectura
    //Comprobamos que se hayan abierto correctamnte
    if (llegada == NULL){
        printf("Error abriendo archivo 1 \n");
        return 1;
    }
    salida = fopen (argv[2], "r");
    if (salida == NULL){
        printf("Error abriendo archivo 2 \n");
        return 1;
    }

	InicializarLista(lista);
    //Guardamos los datos de los ficheros en las listas enlazadas
    LeerFichero(lista, salida, llegada);

    //Cerramos los ficheros en modo lectura
    fclose(salida);
    fclose(llegada);

    do{
        menu();
        scanf("%d", &opcion);
        switch (opcion){
            case 1:
                printf("\n");
                InsertarVuelo(lista);
                printf("\n");
                break;
            case 2:
                printf("\n");
                //Se solicita al usuario la ID del vuelo que quiere buscar
                printf("Introduzca el ID del vuelo en el que desea agregar a un pasajero: ");
                scanf("%d", &ID);
                InsertarPasajeros(lista, ID);
                printf("\n");
                break;
            case 3:
                printf("\n");
                //Se solicita al usuario la ID del vuelo que quiere buscar
                printf("Introduzca el ID del vuelo que desea eliminar: ");
                scanf("%d", &ID);
                EliminarVuelo (lista, ID);
                printf("\n");
                break;
            case 4:
                printf("\n");
                //Se solicita al usuario el DNI del pasajero que quiere buscar
                printf("Introduzca el DNI del pasajero que desea eliminar: ");
                scanf("%d", &DNI);
                EliminarPasajero (lista, DNI);
                printf("\n");
                break;
            case 5:
                printf("\n");
                printf("Los vuelos registrados son:\n");
                MostrarDatos (lista);
                break;
            case 6:
                //OrdenarPasajeros (lista);
                OrdenarVuelos (lista);
                printf("Se han ordenado los vuelos correctamente \n");
                break;
            case 7:
                printf("\n");
                //Se solicita al usuario la ID del vuelo que quiere buscar
                printf("Introduzca el ID del vuelo que desea buscar: ");
                scanf("%d", &ID);
                BuscarVuelos(lista, ID);
                printf("\n");
                break;
            case 8:
                printf("\n");
                //Se solicita al usuario la DNI del pasajero que quiere buscar
                printf("Introduzca el DNI del pasajero que desea buscar: ");
                scanf("%d", &DNI);
                BuscarPasajero(lista, DNI);
                printf("\n");
                break;
            case 9:
                llegada = fopen (argv[1], "w");
                if (llegada == NULL){
                    printf("Error abriendo archivo 1");
                    return 1;
                }
                salida = fopen (argv[2], "w");
                if (salida == NULL){
                    printf("Error abriendo archivo 2");
                    return 1;
                }
                EscribirFicheros(lista, salida, llegada);
                fclose (salida);
                fclose(llegada);
                printf("Escrito la información en los ficheros con éxito\n"); 
                printf("\n");
                // Realizar todos los free necesarios 
                VaciarLista (lista);
                free(lista);
                
                break;
    }
    } while (opcion!=9);

    
    return 0;
}