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
