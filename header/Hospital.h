#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <vector>
#include <string>
#include "Insumo.h"
#include "Paciente.h"

using namespace std;

class Hospital
{
private:
    string codigo;
    string nombre;
    string ciudad;
    int capacidadCamas;
    string especialidades;
    int personalMedico;
    int presupuestoAnual;
    vector<Insumo *> insumos;
    vector<Paciente *> pacientes;


public:
    Hospital(string codigo, string nombre, string ciudad, int capacidadCamas, string especialidades, int personalMedico, int presupuestoAnual);
    void agregarNuevoHospital();
    bool tieneEspecialidad(string especialidad);
    int calcularPacientesAtendidos(int fechaDesde, int fechaHasta); 
    void gestionarListaDeEspera();
    string getCodigo();
    string getCiudad();
    int getCapacidad();
    string getEspecialidades();
    int getPersonal();
    int getPresupuesto();
    void mostrarInformacion();
};

#endif