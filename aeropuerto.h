#ifndef AEROPUERTO_H
#define AEROPUERTO_H
#include <stdio.h>

typedef struct Fecha {
    int dia;
    int mes;
    int anyo;
    int hora;
    int minuto;
}Fecha;

typedef struct DatosPasajeros{
    char* nombre;
    char* apellido;
    int DNI;
    char* destino;
    int asiento_asig;

    struct DatosPasajeros *siguiente;
}Pasajeros;

typedef struct DatosVuelo{
    int ID;
    struct Fecha fecha;
    char* origen;
    char* destino;
    char* aeronave;
    int asientos_total;
    int asientos_ocup;
    Pasajeros *inicioPasajeros;

    struct DatosVuelo *siguiente; 
}Vuelo;

typedef struct DatosLista{
    Vuelo *inicioVuelo; 
    int tamanyo;
}Lista;

void InicializarLista (Lista *lista);
void LeerFichero (Lista *lista, FILE *salida, FILE *llegada);
void CrearNodoVuelo (Lista *lista, Vuelo *n_vuelo);

int ComprobarPais(char *Pais);
int ComprobarAeronave(char *Aeronave);
int CompararFecha (Fecha fecha1, Fecha fecha2);

void InsertarDatosVuelo(Vuelo *nuevo_vuelo);
void InsertarVuelo (Lista *lista);

void InsertarDatosPasajero(Vuelo* punteroVuelos, Pasajeros *nuevo_pasajero);
void InsertarPasajeros (Lista *lista, int ID);

Vuelo *EncontrarIDVuelo(Lista *lista, int ID);
void MostrarDatos(Lista *lista);
void BuscarVuelos (Lista *lista, int ID);
void BuscarPasajero (Lista *lista, int DNI);

void OrdenarPasajeros (Lista *lista);
void OrdenarVuelos (Lista *lista);

void EliminarVuelo (Lista *lista, int ID);
void EliminarPasajero (Lista *lista, int DNI);

void EscribirFicheros (Lista *lista, FILE *salida, FILE *llegada);
void VaciarLista  (Lista *lista);

#endif