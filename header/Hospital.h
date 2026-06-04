#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <vector>
#include <string>
#include <Insumo.h>
#include <Paciente.h>
using namespace std;

class Hospital
{
private:
    string codigo;
    string nombre;
    string ciudad;
    int capacidadCamas;
    string listaEspecialidades;
    int personalMedico;
    int presupuestoAnual;
    vector<Insumo *> insumos;
    vector<Paciente *> pacientes;


public:
    void agregarNuevoHospital();
    bool tieneEspecialidad(string especialidad);
    int calcularPacientesAtendidos(int fechaDesde, int fechaHasta); 
    void gestionarListaDeEspera();
    string getCodigo();

};

#endif