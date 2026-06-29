#ifndef TURNO_H
#define TURNO_H

#include <string>
using namespace std;

class Turno {
private:
    int idTurno;
    int idPaciente;
    int idMedico;
    int fechaTurno; // Formato YYYYMMDD
    string especialidad;
    int duracionMin;

public:
    Turno(int id, int paciente, int medico, int fecha, string esp, int duracion);
    
    int getIdPaciente();
    int getIdMedico();
    int getFecha() const;
    string getEspecialidad();
    int getDuracionMin();
};

#endif