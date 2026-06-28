#include "../header/ArbolDeDiagnosticos.h"
#include <iostream>
#include <algorithm>

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

Diagnostico* ArbolDeDiagnosticos::insertarRec(Diagnostico* actual, Diagnostico* nuevo)
{
    if (actual == nullptr)
        return nuevo;

    if (esMenor(nuevo, actual))
        actual->setIzquierdo(insertarRec(actual->getIzquierdo(), nuevo));
    else
        actual->setDerecho(insertarRec(actual->getDerecho(), nuevo));

    return actual;
}

void ArbolDeDiagnosticos::insertar(Diagnostico* diagnostico)
{
    raiz = insertarRec(raiz, diagnostico);
}

void ArbolDeDiagnosticos::inorder(Diagnostico* actual)
{
    if (actual == nullptr)
        return;

    inorder(actual->getIzquierdo());

    cout << actual->getNombre()
         << " | Frecuencia: "
         << actual->getFrecuencia()
         << endl;

    inorder(actual->getDerecho());
}

void ArbolDeDiagnosticos::listarDiagnosticos()
{
    inorder(raiz);
}

int ArbolDeDiagnosticos::alturaRec(Diagnostico* actual)
{
    if (actual == nullptr)
        return 0;

    int izquierda = alturaRec(actual->getIzquierdo());
    int derecha = alturaRec(actual->getDerecho());

    return 1 + max(izquierda, derecha);
}

int ArbolDeDiagnosticos::altura()
{
    return alturaRec(raiz);
}