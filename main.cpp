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
    int opcionSistema;
    do

    { 
        cout<<"\n===== SISTEMA HOSPITALARIO ====="<<endl;
        cout << "1 - Gestion de Hospitales" << endl;
        cout << "2 - Gestion de Pacientes y Turnos" << endl;
        cout << "0 - Salir del sistema" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcionSistema;
    
        switch(opcionSistema) {

            case 1: {
                int opcionHospital;
                do {
                    cout << "===== GESTION DE HOSPITALES =====" << endl;
                    cout << "1 - Mostrar informacion de un hospital dado su codigo" << endl;
                    cout << "2 - Agregar un nuevo hospital al sistema" << endl;
                    cout << "3 - Eliminar un hospital del sistema" << endl;
                    cout << "4. Listar hospitales ordenados (camas, personal o presupuesto)" << endl;
                    cout << "0 - Volver al menu del sistema hospitalario" << endl;
                    cin>> opcionHospital;

                    switch (opcionHospital) {
                        case 1: {
                            string codigo;
                            cout << "Ingrese el codigo del hospital del cual desea informacion" << endl;
                            cin >> codigo;
                            sistema.mostrarInformacionDeHospital(codigo);
                            volverAlMenu();
                            break;
                        }
        
                        case 2: {
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
                        case 3: {
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
                        case 4: {
                            int criterio;
                            cout<<"Ingrese 1 para odernar por camas, 2 por personal medico, 3 por presupuesto anual : "<<endl;
                            cin>>criterio;
                            vector<Hospital> ordenados = sistema.listarHospitales(criterio);
                            for (size_t i = 0; i < ordenados.size(); i++)
                            {
                                cout << i + 1 << ". Codigo: " << ordenados[i].getCodigo();
                                cout << " | Camas: " << ordenados[i].getCapacidad();
                                cout<< " | Personal: " << ordenados[i].getPersonal();
                                cout<< " | Presupuesto: $" << ordenados[i].getPresupuesto() << endl;
                            }
                            
                        }
                        case 0:
                            cout << "Volviendo al menu del sistema hospitalario" << endl;
                            break;
                        }
            } 
            while (opcionHospital != 0);
            break;
        }
            case 2: {
                int opcionPaciente;
                do {
                    cout << "\n--- GESTION DE PACIENTES Y TURNOS ---" << endl;
                    cout << "1. Total pacientes atendidos por hospital/fecha" << endl;
                    cout << "2. Detectar hospitales con sobrecarga" << endl;
                    cout << "3. Buscar turnos de un paciente (DNI)" << endl;
                    cout << "4. Gestionar lista de espera (Min-Heap)" << endl;
                    cout << "5. Listar turnos de medico en orden cronologico" << endl;
                    cout << "0. Volver al Menu del sistema hospitalario" << endl;
                    cout << "Opcion: ";
                    cin >> opcionPaciente;

                    switch (opcionPaciente) {
                        case 1:
                            
                            volverAlMenu();
                            break;
                        case 2:
                            
                            volverAlMenu();
                            break;
                        case 3:
                            
                            volverAlMenu();
                            break;
                        case 4:
                            
                            volverAlMenu();
                            break;
                        case 5:
                           
                            volverAlMenu();
                            break;
                        case 0:
                            cout << "Volviendo al menu del sistema hospitalario";
                            break;
                    }
                } 
                while (opcionPaciente != 0);
                break; 
            }

            case 0:
                cout << "Cerrando el sistema." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }
        

    } while (opcionSistema != 0);

    return 0;
}