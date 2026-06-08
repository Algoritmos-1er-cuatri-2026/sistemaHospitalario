#ifndef SISTEMAHOSPITALARIO_H
#define SISTEMAHOSPITALARIO_H

#include "Hospital.h"
#include "Paciente.h"
#include "Medico.h"
#include "Diagnostico.h"
#include "Derivacion.h"
#include "Turno.h"
#include "Insumo.h"
#include <vector>
#include <string>
using namespace std;

class SistemaHospitalario
{
private:
    vector<Hospital> listaHospitales;
    vector<Paciente> pacientes;
    vector<Medico> medicos;
    vector<Derivacion> listaDerivaciones;

public:
    void registrarDerivacion(Derivacion nuevaDerivacion);

    //lecturas de archivos ⬆

    void registrarHospital(Hospital nuevoHospital);
    void eliminarHospital(string codigo);
    vector<Hospital> listarHospitales();
    void mostrarInformacionDeHospital(string codigo); // Punto 1
    bool tieneEspecialidad(int codigo, string especialidad);
    int calcularPacientesAtendidos(int codigo, string fecha);
    void gestionarListaDeEspera(int codigo);
    int calcularRuta(Hospital HospitalOrigen, Hospital HospitalDestino);
    vector<Hospital> ordenarPorDisponibilidad(Hospital hospital);
    vector<Hospital> detectarSobrecargaDePacientes(int cantidad);
    void insertarDiagnostico(string nombre, int frecuencia);
    void incrementarFrecuenciaDiagnostico(string nombre);
    vector<Diagnostico> listarDiagnosticos();
    Diagnostico mostrarDiagnosticoFrecuente();
    void eliminarDiagnostico(string nombre);
    bool detectarDesbalanceo();
    vector<Turno> buscarTodosLosTurnos(int dni);
    vector<Turno> listarTurnosCronologicamente(int idMedico);
    void calcularRutaMasRapida(string codigoOrigen, string codigoDestino); // A.5
    int obtenerIndice(string codigo); 
    vector<Hospital> mostrarLista();
};

#endif
