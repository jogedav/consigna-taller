#pragma once

#include <stdio.h>
#include <string.h>


typedef struct {
    int id;
    char marca[30];
    char modelo[30];
    char tipo[30];
    char estado[20];
    float precio;
    int disponible;
} Vehiculo;

typedef struct {
    int idVenta;
    char nombreCliente[50];
    int edadCliente;
    char nombreVendedor[50];
    int idVehiculo;
    float precioVenta;
} Venta;


extern const int maxVehiculos;
extern const char* archivoInventario;
extern const char* archivoVentas;


extern Vehiculo inventario[100];
extern int totalVehiculos;
extern int contadorVentas;

// --- Prototipos de Funciones ---
void cargarInventario();
void guardarInventario();
void generarDatosDePrueba();
void agregarVehiculo();
void buscarVehiculos();
void registrarVenta();
void mostrarVehiculo(Vehiculo v);
void mostrarMenu();
int compararCadenas(const char *s1, const char *s2);