#ifndef ARBOLAVLDIAGNOSTICOS_H
#define ARBOLAVLDIAGNOSTICOS_H

#include "Diagnostico.h"
#include <string>

using namespace std;

class ArbolAVLDiagnosticos
{
private:
    Diagnostico *raiz;

    bool esMenor(Diagnostico *primero, Diagnostico *segundo);

    int alturaRec(Diagnostico *actual);

    int factorBalance(Diagnostico *actual);

    Diagnostico *rotarDerecha(Diagnostico *y);

    Diagnostico *rotarIzquierda(Diagnostico *x);

    Diagnostico *insertarRec(Diagnostico *actual, Diagnostico *nuevo);

    Diagnostico *buscarRec(Diagnostico *actual, string nombre);

    Diagnostico *eliminarRec(Diagnostico *actual, string nombre);

    Diagnostico *minimo(Diagnostico *actual);

    Diagnostico *balancear(Diagnostico *actual);

    void destruirRec(Diagnostico* actual);

    void inorderRec(Diagnostico *actual);

    void mostrarArbolRec(Diagnostico *actual,
                         string prefijo,
                         string lado);

public:
    ArbolAVLDiagnosticos();

    ~ArbolAVLDiagnosticos();

    ArbolAVLDiagnosticos(const ArbolAVLDiagnosticos&) = delete;

    ArbolAVLDiagnosticos& operator=(const ArbolAVLDiagnosticos&) = delete;

    Diagnostico *buscar(string nombre);

    void incrementarFrecuencia(string nombre);
    
    void eliminar(string nombre);

    bool estaVacio();

    void insertar(Diagnostico *diagnostico);

    void listarDiagnosticos();

    void mostrarArbol();

    int altura();
};

#endif