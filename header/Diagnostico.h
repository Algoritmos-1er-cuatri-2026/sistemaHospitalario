#ifndef DIAGNOSTICO_H
#define DIAGNOSTICO_H

#include <string>

using namespace std;

class Diagnostico
{

private:

    string nombre;
    int frecuencia;

    Diagnostico* izquierdo;
    Diagnostico* derecho;

public:

    Diagnostico();

    Diagnostico(string nombre, int frecuencia);

    string getNombre();

    int getFrecuencia();

    void setNombre(string nombre);

    void setFrecuencia(int frecuencia);

    void incrementarFrecuencia();

    Diagnostico* getIzquierdo();

    Diagnostico* getDerecho();

    void setIzquierdo(Diagnostico* izquierdo);

    void setDerecho(Diagnostico* derecho);

};

#endif