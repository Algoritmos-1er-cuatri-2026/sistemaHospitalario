#ifndef SISTEMAHOSPITALARIO_H
#define SISTEMAHOSPITALARIO_H

#include "Hospital.h"
#include "Paciente.h"
#include "Medico.h"
#include "Diagnostico.h"
#include "Derivacion.h"
#include "Turno.h"
#include "Insumo.h"
#include "ArbolDeDiagnosticos.h"
#include <vector>
#include <string>
using namespace std;

enum EstadoHash
{
    LIBRE,
    OCUPADO
};

struct NodoHash
{
    string codigo;
    int indiceVector;
    EstadoHash estado;

    NodoHash()
    {
        codigo = "";
        indiceVector = -1;
        estado = LIBRE;
    }
};

class SistemaHospitalario
{
private:
    vector<Hospital> listaHospitales;
    vector<Paciente> listaPacientes;
    vector<Medico> medicos;
    vector<Derivacion> listaDerivaciones;

    ArbolDeDiagnosticos arbolDiagnosticos;

    vector<NodoHash> tablaHash;
    int tamanoTablaHash;
    bool esPrimo(int numero);
    int proximoPrimo(int numero);
    int calcularHash(string codigo);

public:
    void registrarDerivacion(Derivacion nuevaDerivacion);
    void agregarTurnoAHospital(string codigoHospital, Turno nuevoTurno);
    void registrarPaciente(Paciente nuevoPaciente);

    // funciones usadas para lecturas de archivos ⬆

    void mostrarInformacionDeHospital(string codigo);      // Punto A.1
    void registrarHospital(Hospital nuevoHospital);        // Punto A.2
    void eliminarHospital(string codigo);                  // Punto A.3
    string obtenerHospitalMasCercano(string codigoOrigen); // Punto A.3

    void mostrarPacientes();
    vector<Hospital> listarHospitales(int filtro); // Punto A.4

    void calcularRutaMasRapida(string codigoOrigen, string codigoDestino);                                                                     // A.5
    void agregarDerivacion(Derivacion d);                                                                                                      // Punto A.5
    void ejecutarDijkstra(int indiceOrigen, const std::vector<std::vector<int>> &grafo, std::vector<int> &distancia, std::vector<int> &padre); // A.5
    vector<vector<int>> construirGrafoMatriz();                                                                                                // Punto A.5

    void buscarPorEspecialidad(string especialidad);         // Punto A.6
    bool tieneEspecialidad(int codigo, string especialidad); // Punto A.6

    void inicializarTablaHash();                    // PUNTO A HASH
    void insertarEnHash(string codigo, int indice); // PUNTO A HASH

    vector<Hospital> ordenarPorDisponibilidad(Hospital hospital); // A.6?

    int calcularPacientesAtendidos(string codigoHospital, int fechaDesde, int fechaHasta); // Punto B.1
    vector<Hospital> detectarSobrecargaDePacientes(int cantidad);                          // Punto B.2
    void buscarTurnosPorDNI(int dni);                                                      // Punto B.3
    void gestionarListaDeEspera(int codigo);                                               // Punto B.4
    void listarTurnosCronologicamente(int idMedico);                                       // Punto B.5
    void insertarDiagnostico(string nombre, int frecuencia);

    void incrementarFrecuenciaDiagnostico(string nombre);

    void listarDiagnosticos();

    Diagnostico *mostrarDiagnosticoFrecuente();

    void eliminarDiagnostico(string nombre);

    bool detectarDesbalanceo();

    int alturaArbolDiagnosticos();

    void mostrarArbolDiagnosticos();

    int obtenerIndice(string codigo);
    vector<Hospital> mostrarLista();
};

#endif
