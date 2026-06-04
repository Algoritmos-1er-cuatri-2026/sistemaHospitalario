#include <iostream>
#include <fstream> 
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include "header/SistemaHospitalario.h" 
#include "header/Hospital.h"
#include "header/Derivacion.h"


using namespace std;


void volverAlMenu() // Funciona solo en windows, detiene el sistema hasta que se presione una nueva tecla, asi el menu responde y no vuelve a mostrarse.
{
    system("pause");
}

int main() {
    SistemaHospitalario sistema;
    

    
    //Lectura de archivos

    //hospital:

    ifstream archHospitales("datos/hospitales.txt");

    if (archHospitales.is_open()) {
        string codigo, nombre, ciudad, especialidades;
        int capacidad, personal;
        int presupuesto;

        while (archHospitales >> codigo >> nombre >> ciudad >> capacidad >> especialidades >> personal >> presupuesto) {
            
            Hospital nuevoHospital(codigo, nombre, ciudad, capacidad, especialidades, personal, presupuesto);
            sistema.registrarHospital(nuevoHospital);
        }
        
        archHospitales.close();
        cout << "Base de datos de Hospitales cargada con exito.\n";
    } else {
        cout << "Error: No se pudo abrir el archivo de hospitales.\n";
    }

    



    //Interfaz para el usuario

    cout<<"Bienvenido al Sistema hospitalario \n";
    int opcion;
    do {
    cout << "\n===== SISTEMA HOSPITALARIO =====\n";
    cout << "1 - Mostrar informacion de un hospital dado su codigo\n";
    cout << "0 - Salir\n";
    cout << "Opcion: ";
    
    cin >> opcion;

    switch(opcion)
    {
        case 1:
        {
            string codigo;
            cout<<"Ingrese el codigo del hospital del cual desea informacion \n";
            cin>>codigo;
            sistema.mostrarInformacionDeHospital(codigo);
            volverAlMenu();
        }
        case 2:
            // mostrar hospital
            break;

        case 0:
            cout << "Hasta luego\n";
            break;
    }

} while(opcion != 0);

    return 0;
}