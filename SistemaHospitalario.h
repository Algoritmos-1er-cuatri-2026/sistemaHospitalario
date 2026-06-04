#ifndef SISTEMAHOSPITALARIO_H
#define SISTEMAHOSPITALARIO_H

#include <Hospital.h>
#include <Paciente.h>
#include <Medico.h>
#include <Diagnostico.h>
#include <Turno.h>
#include <Insumo.h>
#include <vector>
#include <string>
using namespace std;

class SistemaHospitalario
{
private:
    vector<Hospital *> hospitales;
    vector<Paciente *> pacientes;
    vector<Medico *> medicos;

public:

    void agregarNuevoHospital();
    void eliminarHospital();
    vector<Hospital *> listarHospitales();
    void mostrarInformaciónDeHospital(int codigo);
    bool tieneEspecialidad(int codigo, string especialidad);
    int calcularPacientesAtendidos(int codigo, string fecha);
    void gestionarListaDeEspera(int codigo);
    int calcularRuta(Hospital HospitalOrigen, Hospital HospitalDestino);
    vector<Hospital *> ordenarPorDisponibilidad(Hospital hospital);
    vector<Hospital *> detectarSobrecargaDePacientes(int cantidad);
    void insertarDiagnostico(string nombre, int frecuencia);
    void incrementarFrecuenciaDiagnostico(string nombre);
    vector<Diagnostico *> listarDiagnosticos();
    Diagnostico mostrarDiagnosticoFrecuente();
    void eliminarDiagnostico(string nombre);
    bool detectarDesbalanceo();
    vector<Turno *> buscarTodosLosTurnos(int dni);
    vector<Turno *> listarTurnosCronologicamente(int idMedico);
    void derivar(Hospital HospitalOrigen, Hospital HospitalDestino,vector<Insumo *>  listaInsumos);
};

#endif