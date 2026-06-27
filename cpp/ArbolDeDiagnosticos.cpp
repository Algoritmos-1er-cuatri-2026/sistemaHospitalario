#include "../header/ArbolDeDiagnosticos.h"

ArbolDeDiagnosticos::ArbolDeDiagnosticos()
{
    raiz = nullptr;
}

bool ArbolDeDiagnosticos::estaVacio()
{
    return raiz == nullptr;
}

bool ArbolDeDiagnosticos::esMenor(Diagnostico* primero, Diagnostico* segundo)
{
    if (primero->getFrecuencia() < segundo->getFrecuencia())
        return true;

    if (primero->getFrecuencia() > segundo->getFrecuencia())
        return false;

    return primero->getNombre() < segundo->getNombre();
}