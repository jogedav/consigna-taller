#include "funciones.h"

int main() {
    int opcion;
    
    cargarInventario();
    
    if (totalVehiculos == 0) {
        generarDatosDePrueba();
    }

    do {
        mostrarMenu();
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                agregarVehiculo();
                break;
            case 2:
                buscarVehiculos();
                break;
            case 3:
                registrarVenta();
                break;
            case 4:
                printf("Saliendo del Sistema SGIC de Ruedas de Oro. ¡Hasta pronto!\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while(opcion != 4);

    return 0;
}