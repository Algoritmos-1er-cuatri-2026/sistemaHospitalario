#include "../header/Paciente.h"

Paciente::Paciente(string hosp, int id, int dni, int fecha, string diag, int prio, float peso)
{
    this->codigoHospital = hosp;
    this->idPaciente = id;
    this->dni = dni;
    this->fechaIngreso = fecha;
    this->diagnostico = diag;
    this->prioridad = prio;
    this->pesoKg = peso;
}

int Paciente::getIdPaciente()
{
    return this->idPaciente;
}
int Paciente::getDni()
{
    return this->dni;
}