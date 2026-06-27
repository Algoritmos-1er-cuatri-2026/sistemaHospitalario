#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
using namespace std;

class Paciente
{
private:
    string codigoHospital;
    int idPaciente;
    int dni;
    int fechaIngreso;
    string diagnostico; 
    int prioridad;
    float pesoKg;

public:
    Paciente(string hosp, int id, int dni, int fecha, string diag, int prio, float peso);
    int getIdPaciente();
    int getDni();
    string getCodHospital();
    void setCodHospital(string codigo);
    int getFechaIngreso();
    string getDiagnostico();
    int getPrioridad();
    float getKg();
};

#endif