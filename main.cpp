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
        cout << "Base de datos de Hospitales cargada con exito." << endl;
    }
    else
    {
        cout << "Error: No se pudo abrir el archivo de hospitales." << endl;
    }

    // Lectura derivacion
    ifstream archDerivacion("datos/derivaciones.txt");

    if (archDerivacion.is_open())
    {
        string origen, destino;
        int tiempo;

        while (archDerivacion >> origen >> destino >> tiempo)
        {

            Derivacion nuevaDeri(origen, destino, tiempo);
            sistema.agregarDerivacion(nuevaDeri);
        }

        archDerivacion.close();
        cout << "Base de datos de derivaciones cargada con exito." << endl;
    }
    else
    {
        cout << "Error: No se pudo abrir el archivo de derivaciones." << endl;
    }

    // Lectura de turnos
    ifstream archTurnos("datos/turnos.txt");

    if (archTurnos.is_open())
    {
        string codigoHospital, especialidad;
        int idTurno, idPaciente, idMedico, fechaTurno, duracionMin;

        while (archTurnos >> codigoHospital >> idTurno >> idPaciente >> idMedico >> fechaTurno >> especialidad >> duracionMin)
        {
            Turno nuevoTurno(idTurno, idPaciente, idMedico, fechaTurno, especialidad, duracionMin);
            sistema.agregarTurnoAHospital(codigoHospital, nuevoTurno);
        }

        archTurnos.close();
        cout << "Base de datos de Turnos cargada con exito." << endl;
    }
    else
    {
        cout << "Error: No se pudo abrir el archivo de turnos." << endl;
    }

    // Lectura de pacientes
    ifstream archPacientes("datos/pacientes.txt");

    if (archPacientes.is_open())
    {
        string codigoHospital, diagnostico;
        int idPaciente, dni, fechaIngreso, prioridad;
        float pesoKg;

        while (archPacientes >> codigoHospital >> idPaciente >> dni >> fechaIngreso >> diagnostico >> prioridad >> pesoKg)
        {
            Paciente nuevoPaciente(codigoHospital, idPaciente, dni, fechaIngreso, diagnostico, prioridad, pesoKg);
            sistema.registrarPaciente(nuevoPaciente);
        }

        archPacientes.close();
        cout << "Base de datos de Pacientes cargada con exito." << endl;
    }
    else
    {
        cout << "Error: No se pudo abrir el archivo de pacientes." << endl;
    }

    // Interfaz para el usuario

    cout << "Bienvenido al Sistema hospitalario" << endl;
    int opcionSistema;
    do

    {
        cout << "===== SISTEMA HOSPITALARIO =====" << endl;
        cout << "1 - Gestion de Hospitales" << endl;
        cout << "2 - Gestion de Pacientes y Turnos" << endl;
        cout << "0 - Salir del sistema" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcionSistema;

        switch (opcionSistema)
        {

        case 1:
        {
            int opcionHospital;
            do
            {
                cout << "===== GESTION DE HOSPITALES =====" << endl;
                cout << "1 - Mostrar informacion de un hospital dado su codigo" << endl;
                cout << "2 - Agregar un nuevo hospital al sistema" << endl;
                cout << "3 - Eliminar un hospital del sistema" << endl;
                cout << "4. Listar hospitales ordenados (camas, personal o presupuesto)" << endl;
                cout << "5. Calcular lista mas rapida entre dos hospitales" << endl;
                cout << "6. Buscar hospitales por especialidad ordenados por capacidad de camas." << endl;
                cout << "0 - Volver al menu del sistema hospitalario" << endl;
                cin >> opcionHospital;

                switch (opcionHospital)
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

                    // FALTO reasignar sus pacientes activos al hospital más cercano disponible
                }
                case 4:
                {
                    int criterio;
                    cout << "Ingrese 1 para odernar por camas, 2 por personal medico, 3 por presupuesto anual : " << endl;
                    cin >> criterio;
                    vector<Hospital> ordenados = sistema.listarHospitales(criterio);
                    for (size_t i = 0; i < ordenados.size(); i++)
                    {
                        cout << i + 1 << ". Codigo: " << ordenados[i].getCodigo();
                        cout << " | Camas: " << ordenados[i].getCapacidad();
                        cout << " | Personal: " << ordenados[i].getPersonal();
                        cout << " | Presupuesto: $" << ordenados[i].getPresupuesto() << endl;
                    }
                }
                case 5:
                {
                    string origen, destino;
                    cout << "Ingrese el codigo del hopital origen : " << endl;
                    cin >> origen;
                    cout << "Ingrese el codigo del hopital destino : " << endl;
                    cin >> destino;
                    sistema.calcularRutaMasRapida(origen, destino);
                }
                case 6:
                {
                    string especialidad;
                    cout << "Ingrese la especialidad buscada" << endl;
                    cin >> especialidad;
                    sistema.buscarPorEspecialidad(especialidad);
                }
                case 0:
                    cout << "Volviendo al menu del sistema hospitalario" << endl;
                    break;
                }
            } while (opcionHospital != 0);
            break;
        }
        case 2:
        {
            int opcionPaciente;

            do
            {
                cout << "--- GESTION DE PACIENTES Y TURNOS ---" << endl;
                cout << "1. Total pacientes atendidos por hospital/fecha" << endl;
                cout << "2. Detectar hospitales con sobrecarga" << endl;
                cout << "3. Buscar turnos de un paciente (DNI)" << endl;
                cout << "4. Gestionar lista de espera (Min-Heap)" << endl;
                cout << "5. Listar turnos de medico en orden cronologico" << endl;
                cout << "0. Volver al Menu del sistema hospitalario" << endl;
                cout << "Opcion: ";
                cin >> opcionPaciente;

                switch (opcionPaciente)
                {
                case 1:
                {
                    string codHospital;
                    int fDesde, fHasta, totalAtendidos;

                    cout << "--- CALCULAR PACIENTES ATENDIDOS ---" << endl;
                    cout << "Ingrese el codigo del hospital (ej. HGA): " << endl;
                    cin >> codHospital;

                    cout << "Ingrese la fecha de inicio (YYYYMMDD): " << endl;
                    cin >> fDesde;

                    cout << "Ingrese la fecha de fin (YYYYMMDD): " << endl;
                    cin >> fHasta;

                    totalAtendidos = sistema.calcularPacientesAtendidos(codHospital, fDesde, fHasta);

                    cout << "Total de pacientes atendidos: " << totalAtendidos << endl;

                    volverAlMenu();
                    break;
                }

                case 2:
                {

                    volverAlMenu();
                    break;
                }
                case 3:
                {
                    int dniBusqueda;
                    cout << "--- BUSCAR TURNOS POR DNI ---" << endl;
                    cout << "Ingrese el DNI del paciente: " << endl;
                    cin >> dniBusqueda;

                    cout << endl;
                    sistema.buscarTurnosPorDNI(dniBusqueda);
                    //Ver si usar algun algoritmo de busqueda en lugar del secuencial usado

                    volverAlMenu();
                    break;
                }
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
            } while (opcionPaciente != 0);
            break;
        }

        case 0:
            cout << "Cerrando el sistema." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }

    } while (opcionSistema != 0);

    return 0;
}