#ifndef ARBOLDIAGNOSTICOS_H
#define ARBOLDIAGNOSTICOS_H

#include "Diagnostico.h"

using namespace std;

class ArbolDeDiagnosticos
{

private:

    Diagnostico* raiz;

    bool esMenor(Diagnostico* primero, Diagnostico* segundo);

    Diagnostico* insertarRec(Diagnostico* actual, Diagnostico* nuevo);

    Diagnostico* buscarRec(Diagnostico* actual, string nombre);

    void inorder(Diagnostico* actual);

    int alturaRec(Diagnostico* actual);

public:

    ArbolDeDiagnosticos();

    bool estaVacio();

    void insertar(Diagnostico* diagnostico);

    Diagnostico* buscar(string nombre);

    void listarDiagnosticos();

    int altura();

};

#endif