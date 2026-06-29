#ifndef ARBOLDIAGNOSTICOS_H
#define ARBOLDIAGNOSTICOS_H

#include "Diagnostico.h"
#include <string>

using namespace std;

class ArbolDeDiagnosticos
{
private:
    Diagnostico* raiz;

    bool esMenor(Diagnostico* primero, Diagnostico* segundo);

    Diagnostico* insertarRec(Diagnostico* actual, Diagnostico* nuevo);

    Diagnostico* buscarRec(Diagnostico* actual, string nombre);

    void destruirRec(Diagnostico* actual);

    void inorderRec(Diagnostico* actual);

    Diagnostico* buscarMayorRec(Diagnostico* actual);

    int alturaRec(Diagnostico* actual);

    bool estaDesbalanceadoRec(Diagnostico* actual);

    Diagnostico* eliminarNodoRec(Diagnostico* actual, Diagnostico* objetivo);

    Diagnostico* extraerMinimo(Diagnostico* actual, Diagnostico*& minimoExtraido);

    void mostrarArbolRec(Diagnostico* actual,
                     string prefijo,
                     string lado);

public:
    ArbolDeDiagnosticos();

    ~ArbolDeDiagnosticos();

    ArbolDeDiagnosticos(const ArbolDeDiagnosticos&) = delete;

    ArbolDeDiagnosticos& operator=(const ArbolDeDiagnosticos&) = delete;

    bool estaVacio();

    void insertar(Diagnostico* diagnostico);

    Diagnostico* buscar(string nombre);

    void incrementarFrecuencia(string nombre);

    void listarDiagnosticos();

    Diagnostico* diagnosticoMasFrecuente();

    void eliminar(string nombre);

    int altura();

    bool estaDesbalanceado();

    void mostrarArbol();
};

#endif