#include "funciones.h"


const int maxVehiculos = 100;
const char* archivoInventario = "inventario.txt";
const char* archivoVentas = "ventas.txt";

Vehiculo inventario[100];
int totalVehiculos = 0;
int contadorVentas = 0;


int compararCadenas(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        char c1 = s1[i];
        char c2 = s2[i];
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32; 
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32; 
        if (c1 != c2) return 0; 
        i++;
    }
    return (s1[i] == '\0' && s2[i] == '\0'); 
}

void mostrarMenu() {
    printf("\n========================================\n");
    printf("   SGIC - CONCESIONARIA RUEDAS DE ORO   \n");
    printf("========================================\n");
    printf("1. Agregar nuevo vehiculo al inventario\n");
    printf("2. Buscar vehiculos (Presupuesto/Filtros)\n");
    printf("3. Registrar una venta\n");
    printf("4. Salir\n");
    printf("Seleccione una opcion: ");
}

void cargarInventario() {
    FILE *archivo = fopen(archivoInventario, "r");
    if (archivo == NULL) {
        return; 
    }

    totalVehiculos = 0;
    while (fscanf(archivo, "%d %s %s %s %s %f %d", 
                  &inventario[totalVehiculos].id,
                  inventario[totalVehiculos].marca,
                  inventario[totalVehiculos].modelo,
                  inventario[totalVehiculos].tipo,
                  inventario[totalVehiculos].estado,
                  &inventario[totalVehiculos].precio,
                  &inventario[totalVehiculos].disponible) == 7) {
        totalVehiculos++;
    }
    fclose(archivo);
}

void guardarInventario() {
    FILE *archivo = fopen(archivoInventario, "w");
    if (archivo == NULL) {
        printf("Error al guardar el inventario en el archivo.\n");
        return;
    }

    for (int i = 0; i < totalVehiculos; i++) {
        fprintf(archivo, "%d %s %s %s %s %.2f %d\n", 
                inventario[i].id,
                inventario[i].marca,
                inventario[i].modelo,
                inventario[i].tipo,
                inventario[i].estado,
                inventario[i].precio,
                inventario[i].disponible);
    }
    fclose(archivo);
}

void agregarVehiculo() {
    if (totalVehiculos >= maxVehiculos) {
        printf("Error: Inventario lleno.\n");
        return;
    }
    
    Vehiculo v;
    v.id = totalVehiculos + 1;
    
    printf("Ingrese Marca: ");
    scanf("%s", v.marca);
    printf("Ingrese Modelo: ");
    scanf("%s", v.modelo);
    printf("Ingrese Tipo (ej. Camioneta, Sedan): ");
    scanf("%s", v.tipo);
    printf("Ingrese Estado (Nuevo, Usado): ");
    scanf("%s", v.estado);
    printf("Ingrese Precio: ");
    scanf("%f", &v.precio);
    v.disponible = 1;
    
    inventario[totalVehiculos] = v;
    totalVehiculos++;
    
    guardarInventario(); 
    printf("Vehiculo agregado exitosamente con el ID: %d\n", v.id);
}

void buscarVehiculos() {
    float presupuestoMax;
    char tipoBuscado[30];
    char marcaBuscada[30];
    char estadoBuscado[20];
    int encontrados = 0;

    printf("\n--- Busqueda de Vehiculos ---\n");
    printf("Ingrese presupuesto maximo (ej. 14000): ");
    scanf("%f", &presupuestoMax);
    printf("Ingrese tipo de vehiculo (ej. Camioneta): ");
    scanf("%s", tipoBuscado);
    printf("Ingrese estado (ej. Usado): ");
    scanf("%s", estadoBuscado);
    printf("Ingrese marca preferida (ej. Chevrolet): ");
    scanf("%s", marcaBuscada);

    printf("\nResultados de la busqueda:\n");
    for (int i = 0; i < totalVehiculos; i++) {
        if (inventario[i].disponible == 1 && inventario[i].precio <= presupuestoMax) {
            if (compararCadenas(inventario[i].tipo, tipoBuscado) == 1 || 
                compararCadenas(inventario[i].marca, marcaBuscada) == 1) {
                mostrarVehiculo(inventario[i]);
                encontrados++;
            }
        }
    }
    
    if (encontrados == 0) {
        printf("No se encontraron vehiculos que se ajusten a los criterios.\n");
    }
}

void registrarVenta() {
    int idBuscar, indiceVehiculo = -1;
    Venta nuevaVenta;

    printf("\n--- Registro de Venta ---\n");
    printf("Ingrese el ID del vehiculo a vender: ");
    scanf("%d", &idBuscar);

    for (int i = 0; i < totalVehiculos; i++) {
        if (inventario[i].id == idBuscar && inventario[i].disponible == 1) {
            indiceVehiculo = i;
            break;
        }
    }

    if (indiceVehiculo == -1) {
        printf("Error: Vehiculo no encontrado o ya fue vendido.\n");
        return;
    }

    printf("Nombre del cliente: ");
    scanf("%s", nuevaVenta.nombreCliente);
    printf("Edad del cliente: ");
    scanf("%d", &nuevaVenta.edadCliente);
    printf("Nombre del vendedor: ");
    scanf("%s", nuevaVenta.nombreVendedor);

    nuevaVenta.idVehiculo = idBuscar;
    nuevaVenta.precioVenta = inventario[indiceVehiculo].precio;
    
    contadorVentas++;
    nuevaVenta.idVenta = contadorVentas;

    FILE *archivoVentasPrt = fopen(archivoVentas, "a"); 
    if (archivoVentasPrt != NULL) {
        fprintf(archivoVentasPrt, "%d %s %d %s %d %.2f\n", 
                nuevaVenta.idVenta, nuevaVenta.nombreCliente, nuevaVenta.edadCliente, 
                nuevaVenta.nombreVendedor, nuevaVenta.idVehiculo, nuevaVenta.precioVenta);
        fclose(archivoVentasPrt);
    }

    inventario[indiceVehiculo].disponible = 0;
    guardarInventario();

    printf("\n¡Venta registrada con exito!\n");
    printf("El vehiculo ID %d ahora esta marcado como VENDIDO.\n", idBuscar);
}

void mostrarVehiculo(Vehiculo v) {
    printf("ID: %d | Marca: %s | Modelo: %s | Tipo: %s | Estado: %s | Precio: $%.2f\n", 
           v.id, v.marca, v.modelo, v.tipo, v.estado, v.precio);
}

void generarDatosDePrueba() {
    Vehiculo v1 = {1, "Chevrolet", "D-Max", "Camioneta", "Usado", 13500.00, 1};
    Vehiculo v2 = {2, "Toyota", "Hilux", "Camioneta", "Usado", 15000.00, 1};
    Vehiculo v3 = {3, "Chevrolet", "Sail", "Sedan", "Nuevo", 14000.00, 1};
    Vehiculo v4 = {4, "Ford", "Ranger", "Camioneta", "Usado", 12500.00, 1};

    inventario[0] = v1;
    inventario[1] = v2;
    inventario[2] = v3;
    inventario[3] = v4;
    totalVehiculos = 4;
    
    guardarInventario();
}