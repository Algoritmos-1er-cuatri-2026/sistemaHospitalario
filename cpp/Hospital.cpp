#include "../header/Hospital.h"
#include <iostream>

using namespace std;

Hospital::Hospital(string codigo, string nombre, string ciudad, int capacidadCamas, string especialidades, int personalMedico, int presupuestoAnual){
    this->codigo = codigo;
    this->nombre = nombre;
    this->ciudad = ciudad;
    this->capacidadCamas = capacidadCamas;
    this->especialidades = especialidades;
    this->personalMedico = personalMedico;
    this->presupuestoAnual = presupuestoAnual;
}
    
string Hospital::getCodigo() {
    return this->codigo;
}

string Hospital::getCiudad(){
    return this->ciudad;
}

int Hospital::getCapacidad(){
    return this->capacidadCamas;
  }

string Hospital::getEspecialidades(){
    return this->especialidades;
  }
int Hospital::getPersonal(){
    return this->personalMedico;
    }
int Hospital::getPresupuesto(){
    return this->presupuestoAnual;
    }

void Hospital::mostrarInformacion() {
    cout << "Codigo: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Ciudad: " << ciudad << endl;
    cout << "Capacidad: " << capacidadCamas << endl;
    cout << "Especialidades: " << especialidades << endl;
    cout << "Personal: " << personalMedico << endl;
    cout << "Presupuesto: " << presupuestoAnual << endl;
}

bool Hospital::tieneEspecialidad(string especialidad) {

    string especialidadHospitalMin = "";
    string especialidadBusquedaMin = "";

    for (size_t i = 0; i < this->especialidades.length(); i++) // pasamos a minusculas las especialidades del hospital
    {
        char c = this->especialidades[i];
        if (c>= 'A' && c<= 'Z') {
            c = c+32; // la diferencia ascii entre mayus y minusculas es siempre 32
        }
        especialidadHospitalMin += c;
    }

    for (size_t i = 0; i < especialidad.length(); i++) // pasamos a minuscula las especialidades buscadas por el usuario
    {
        char c = especialidad[i];
        if (c>= 'A' && c<= 'Z') {
            c = c+32;
        }
        especialidadBusquedaMin += c;
    }

    
    if (especialidadHospitalMin.find(especialidadBusquedaMin) != string::npos) { //!= string::npos se usa para representar los no encontrados.. sin eso cuando falla c++ devuelve un -1 y entra igual al if.
        return true;
    }
    return false;
}

void Hospital::registrarTurno(Turno nuevoTurno) {
    this->turnos.push_back(nuevoTurno);
}

vector<Turno> Hospital::getTurnos() {
    return this->turnos;
}
