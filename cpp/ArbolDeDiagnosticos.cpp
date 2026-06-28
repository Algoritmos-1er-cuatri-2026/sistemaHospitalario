#include "../header/ArbolDeDiagnosticos.h"

#include <iostream>

using namespace std;

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

void ArbolDeDiagnosticos::insertar(Diagnostico* diagnostico)
{
    raiz = insertarRec(raiz, diagnostico);
}

Diagnostico* ArbolDeDiagnosticos::insertarRec(Diagnostico* actual, Diagnostico* nuevo)
{
    if (actual == nullptr)
    {
        return nuevo;
    }

    if (esMenor(nuevo, actual))
    {
        actual->setIzquierdo(insertarRec(actual->getIzquierdo(), nuevo));
    }
    else
    {
        actual->setDerecho(insertarRec(actual->getDerecho(), nuevo));
    }

    return actual;
}

Diagnostico* ArbolDeDiagnosticos::buscar(string nombre)
{
    return buscarRec(raiz, nombre);
}

Diagnostico* ArbolDeDiagnosticos::buscarRec(Diagnostico* actual, string nombre)
{
    if (actual == nullptr)
        return nullptr;

    if (actual->getNombre() == nombre)
        return actual;

    Diagnostico* encontrado = buscarRec(actual->getIzquierdo(), nombre);

    if (encontrado != nullptr)
        return encontrado;

    return buscarRec(actual->getDerecho(), nombre);
}

void ArbolDeDiagnosticos::listarDiagnosticos()
{
    inorderRec(raiz);
}

void ArbolDeDiagnosticos::inorderRec(Diagnostico* actual)
{
    if (actual == nullptr)
        return;

    inorderRec(actual->getIzquierdo());

    cout << actual->getNombre()
         << " - Frecuencia: "
         << actual->getFrecuencia()
         << endl;

    inorderRec(actual->getDerecho());
}

Diagnostico* ArbolDeDiagnosticos::buscarMayorRec(Diagnostico* actual)
{
    if (actual == nullptr)
        return nullptr;

    while (actual->getDerecho() != nullptr)
    {
        actual = actual->getDerecho();
    }

    return actual;
}

Diagnostico* ArbolDeDiagnosticos::diagnosticoMasFrecuente()
{
    return buscarMayorRec(raiz);
}

int ArbolDeDiagnosticos::altura()
{
    return alturaRec(raiz);
}

int ArbolDeDiagnosticos::alturaRec(Diagnostico* actual)
{
    if (actual == nullptr)
        return -1;

    int izquierda = alturaRec(actual->getIzquierdo());
    int derecha = alturaRec(actual->getDerecho());

    if (izquierda > derecha)
        return izquierda + 1;

    return derecha + 1;
}

bool ArbolDeDiagnosticos::estaDesbalanceado()
{
    if (raiz == nullptr)
        return false;

    int izquierda = alturaRec(raiz->getIzquierdo());
    int derecha = alturaRec(raiz->getDerecho());

    int diferencia = izquierda - derecha;

    if (diferencia < 0)
        diferencia *= -1;

    return diferencia > 2;
}

Diagnostico* ArbolDeDiagnosticos::minimo(Diagnostico* actual)
{
    while (actual->getIzquierdo() != nullptr)
    {
        actual = actual->getIzquierdo();
    }

    return actual;
}

void ArbolDeDiagnosticos::eliminar(string nombre)
{
    raiz = eliminarRec(raiz, nombre);
}

Diagnostico* ArbolDeDiagnosticos::eliminarRec(Diagnostico* actual, string nombre)
{
    if (actual == nullptr)
    {
        return nullptr;
    }

    if (actual->getNombre() == nombre)
    {
        if (actual->getIzquierdo() == nullptr)
        {
            return actual->getDerecho();
        }

        if (actual->getDerecho() == nullptr)
        {
            return actual->getIzquierdo();
        }

        Diagnostico* sucesor = minimo(actual->getDerecho());

        actual->setNombre(sucesor->getNombre());
        actual->setFrecuencia(sucesor->getFrecuencia());

        actual->setDerecho(eliminarRec(actual->getDerecho(), sucesor->getNombre()));

        return actual;
    }

    actual->setIzquierdo(eliminarRec(actual->getIzquierdo(), nombre));
    actual->setDerecho(eliminarRec(actual->getDerecho(), nombre));

    return actual;
}

void ArbolDeDiagnosticos::incrementarFrecuencia(string nombre)
{
    Diagnostico* encontrado = buscar(nombre);

    if (encontrado == nullptr)
    {
        return;
    }

    string nombreDiag = encontrado->getNombre();
    int frecuenciaNueva = encontrado->getFrecuencia() + 1;

    eliminar(nombreDiag);

    Diagnostico* nuevo = new Diagnostico(nombreDiag, frecuenciaNueva);

    insertar(nuevo);
}