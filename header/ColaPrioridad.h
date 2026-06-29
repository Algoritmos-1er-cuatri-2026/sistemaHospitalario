#ifndef COLAPRIORIDAD_H
#define COLAPRIORIDAD_H

#include <vector>
#include "Paciente.h"

class ColaPrioridad {
private:
    vector<Paciente> heap;

    void flotar(int indice);
    void hundir(int indice);
    bool tieneMayorPrioridad(Paciente p1, Paciente p2);

public:
    ColaPrioridad();
    void encolar(Paciente p);
    Paciente desencolar();
    void actualizarPrioridad(int idPaciente, int nuevaPrioridad);
    bool esVacia();
};

#endif