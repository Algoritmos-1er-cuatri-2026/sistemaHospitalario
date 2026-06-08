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

int main()
{
    SistemaHospitalario sistema;

    // Lectura de archivos

    // hospital:

    ifstream archHospitales("datos/hospitales.txt");

    if (archHospitales.is_open())
    {
        string codigo, nombre, ciudad, especialidades;
        int capacidad, personal;
        int presupuesto;

        while (archHospitales >> codigo >> nombre >> ciudad >> capacidad >> especialidades >> personal >> presupuesto)
        {

            Hospital nuevoHospital(codigo, nombre, ciudad, capacidad, especialidades, personal, presupuesto);
            sistema.registrarHospital(nuevoHospital);
        }

        archHospitales.close();
        cout << "Base de datos de Hospitales cargada con exito.\n";
    }
    else
    {
        cout << "Error: No se pudo abrir el archivo de hospitales.\n";
    }

    // Interfaz para el usuario

    cout << "Bienvenido al Sistema hospitalario" << endl;
    int opcion;
    do
    {
        cout << "===== SISTEMA HOSPITALARIO =====" << endl;
        cout << "1 - Mostrar informacion de un hospital dado su codigo" << endl;
        cout << "2 - Agregar un nuevo hospital al sistema" << endl;
        cout << "3 - Eliminar un hospital del sistema" << endl;
        cout << "0 - Salir" << endl;
        cout << "Opcion: " << endl;

        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            string codigo;
            cout << "Ingrese el codigo del hospital del cual desea informacion" << endl;
            cin >> codigo;
            sistema.mostrarInformacionDeHospital(codigo);
            volverAlMenu();
            break;
        }
        case 2:
        {
            string codigo, nombre, ciudad, especialidades;
            int capacidadCamas, personalMedico, presupuestoAnual;

            cout << "--- REGISTRAR NUEVO HOSPITAL ---" << endl;

            cout << "Ingrese el codigo: ";
            cin >> codigo;

            cout << "Ingrese el nombre: ";
            cin >> nombre;

            cout << "Ingrese la ciudad: ";
            cin >> ciudad;

            cout << "Ingrese la capacidad de camas: ";
            cin >> capacidadCamas;

            cout << "Ingrese las especialidades: ";
            cin >> especialidades;

            cout << "Ingrese la cantidad de personal medico: ";
            cin >> personalMedico;

            cout << "Ingrese el presupuesto anual: ";
            cin >> presupuestoAnual;

            Hospital nuevoHospital(codigo, nombre, ciudad, capacidadCamas, especialidades, personalMedico, presupuestoAnual);

            sistema.registrarHospital(nuevoHospital);

            cout << "Hospital registrado correctamente" << endl;

            volverAlMenu();
            break;
        }
        case 3:
        {
            cout << "--- ELIMINAR HOSPITAL ---" << endl;
            string codigo;
            cout << "Ingrese el codigo: ";
            cin >> codigo;
            int indice = sistema.obtenerIndice(codigo);
            sistema.eliminarHospital(codigo);

            cout << "Hospital eliminado correctamente" << endl;
            volverAlMenu();
            break;

            //FALTO reasignar sus pacientes activos al hospital más cercano disponible
        }

        case 0:
            cout << "Hasta luego" << endl;
            break;
        }

    } while (opcion != 0);

    return 0;
}