#ifndef PACIENTE_H
#define PACIENTE_H

#include <vector>
#include <string>
#include <Turno.h>
using namespace std;

class Paciente
{
private:
    int idPaciente;
    int dni;
    int fechaIngreso;
    string diagnostico; //Tipo Diagnostico en lugar de string?
    int prioridad;
    float pesoKg;
    vector<Turno*> turnos;

public:
    void listarTurnos();
};

#endif