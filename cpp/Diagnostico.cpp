#include "../header/Diagnostico.h"

Diagnostico::Diagnostico()
{
    nombre = "";
    frecuencia = 0;

    izquierdo = nullptr;
    derecho = nullptr;
}

Diagnostico::Diagnostico(string nombre, int frecuencia)
{
    this->nombre = nombre;
    this->frecuencia = frecuencia;

    izquierdo = nullptr;
    derecho = nullptr;
}

string Diagnostico::getNombre()
{
    return nombre;
}

int Diagnostico::getFrecuencia()
{
    return frecuencia;
}

void Diagnostico::setNombre(string nombre)
{
    this->nombre = nombre;
}

void Diagnostico::setFrecuencia(int frecuencia)
{
    this->frecuencia = frecuencia;
}

void Diagnostico::incrementarFrecuencia()
{
    frecuencia++;
}

Diagnostico* Diagnostico::getIzquierdo()
{
    return izquierdo;
}

Diagnostico* Diagnostico::getDerecho()
{
    return derecho;
}

void Diagnostico::setIzquierdo(Diagnostico* izquierdo)
{
    this->izquierdo = izquierdo;
}

void Diagnostico::setDerecho(Diagnostico* derecho)
{
    this->derecho = derecho;
}