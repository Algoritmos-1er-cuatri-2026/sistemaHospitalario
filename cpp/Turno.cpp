#include "../header/Turno.h"

Turno::Turno(int id, int paciente, int medico, int fecha, string esp, int duracion) {
    this->idTurno = id;
    this->idPaciente = paciente;
    this->idMedico = medico;
    this->fechaTurno = fecha;
    this->especialidad = esp;
    this->duracionMin = duracion;
}

int Turno::getIdPaciente() { return this->idPaciente; }
int Turno::getIdMedico() { return this->idMedico; }
int Turno::getFecha() const{ return this->fechaTurno; }
string Turno::getEspecialidad() { return this->especialidad; }
int Turno::getDuracionMin() { return this->duracionMin; }