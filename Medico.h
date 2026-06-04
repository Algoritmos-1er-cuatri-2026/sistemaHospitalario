#ifndef MEDICO_H
#define MEDICO_H

#include <vector>
#include <string>
#include <Turno.h>
using namespace std;

class Medico
{
private:
    int idMedico;
    string nombre;
    string especialidad;
    vector<Turno*> turnos;
public:
    void listarTurnosCronologicamente();
};

#endif