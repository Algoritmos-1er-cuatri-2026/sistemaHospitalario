#include "../header/ArbolAVLDiagnosticos.h"
#include <iostream>

using namespace std;

ArbolAVLDiagnosticos::ArbolAVLDiagnosticos()
{
    raiz = nullptr;
}

ArbolAVLDiagnosticos::~ArbolAVLDiagnosticos()
{
    destruirRec(raiz);
    raiz = nullptr;
}

void ArbolAVLDiagnosticos::destruirRec(Diagnostico *actual)
{
    if (actual == nullptr)
        return;

    destruirRec(actual->getIzquierdo());
    destruirRec(actual->getDerecho());

    delete actual;
}

bool ArbolAVLDiagnosticos::estaVacio()
{
    return raiz == nullptr;
}

bool ArbolAVLDiagnosticos::esMenor(Diagnostico *primero, Diagnostico *segundo)
{
    if (primero->getFrecuencia() < segundo->getFrecuencia())
        return true;

    if (primero->getFrecuencia() > segundo->getFrecuencia())
        return false;

    return primero->getNombre() < segundo->getNombre();
}

int ArbolAVLDiagnosticos::altura()
{
    return alturaRec(raiz);
}

int ArbolAVLDiagnosticos::alturaRec(Diagnostico *actual)
{
    if (actual == nullptr)
        return -1;

    int alturaIzquierda = alturaRec(actual->getIzquierdo());
    int alturaDerecha = alturaRec(actual->getDerecho());

    if (alturaIzquierda > alturaDerecha)
        return alturaIzquierda + 1;

    return alturaDerecha + 1;
}

int ArbolAVLDiagnosticos::factorBalance(Diagnostico *actual)
{
    if (actual == nullptr)
        return 0;

    return alturaRec(actual->getIzquierdo()) - alturaRec(actual->getDerecho());
}

Diagnostico *ArbolAVLDiagnosticos::rotarDerecha(Diagnostico *y)
{
    Diagnostico *x = y->getIzquierdo();
    Diagnostico *t2 = x->getDerecho();

    x->setDerecho(y);
    y->setIzquierdo(t2);

    return x;
}

Diagnostico *ArbolAVLDiagnosticos::rotarIzquierda(Diagnostico *x)
{
    Diagnostico *y = x->getDerecho();
    Diagnostico *t2 = y->getIzquierdo();

    y->setIzquierdo(x);
    x->setDerecho(t2);

    return y;
}

void ArbolAVLDiagnosticos::insertar(Diagnostico *diagnostico)
{
    if (diagnostico == nullptr)
        return;

    diagnostico->setIzquierdo(nullptr);
    diagnostico->setDerecho(nullptr);

    raiz = insertarRec(raiz, diagnostico);
}

Diagnostico *ArbolAVLDiagnosticos::insertarRec(Diagnostico *actual, Diagnostico *nuevo)
{
    if (actual == nullptr)
        return nuevo;

    if (esMenor(nuevo, actual))
        actual->setIzquierdo(insertarRec(actual->getIzquierdo(), nuevo));
    else
        actual->setDerecho(insertarRec(actual->getDerecho(), nuevo));

    int balance = factorBalance(actual);

    if (balance > 1 && esMenor(nuevo, actual->getIzquierdo()))
        return rotarDerecha(actual);

    if (balance < -1 && !esMenor(nuevo, actual->getDerecho()))
        return rotarIzquierda(actual);

    if (balance > 1 && !esMenor(nuevo, actual->getIzquierdo()))
    {
        actual->setIzquierdo(rotarIzquierda(actual->getIzquierdo()));
        return rotarDerecha(actual);
    }

    if (balance < -1 && esMenor(nuevo, actual->getDerecho()))
    {
        actual->setDerecho(rotarDerecha(actual->getDerecho()));
        return rotarIzquierda(actual);
    }

    return actual;
}

void ArbolAVLDiagnosticos::listarDiagnosticos()
{
    if (raiz == nullptr)
    {
        cout << "No hay diagnosticos cargados en el AVL." << endl;
        return;
    }

    inorderRec(raiz);
}

void ArbolAVLDiagnosticos::inorderRec(Diagnostico *actual)
{
    if (actual == nullptr)
        return;

    inorderRec(actual->getIzquierdo());

    cout << "Diagnostico: " << actual->getNombre()
         << " | Frecuencia: " << actual->getFrecuencia()
         << endl;

    inorderRec(actual->getDerecho());
}

void ArbolAVLDiagnosticos::mostrarArbol()
{
    if (raiz == nullptr)
    {
        cout << "No hay diagnosticos cargados en el AVL." << endl;
        return;
    }

    cout << "Raiz: "
         << raiz->getNombre()
         << " ("
         << raiz->getFrecuencia()
         << ")"
         << endl;

    if (raiz->getIzquierdo() != nullptr)
    {
        mostrarArbolRec(raiz->getIzquierdo(), "", "Izq");
    }

    if (raiz->getDerecho() != nullptr)
    {
        mostrarArbolRec(raiz->getDerecho(), "", "Der");
    }
}

void ArbolAVLDiagnosticos::mostrarArbolRec(
    Diagnostico *actual,
    string prefijo,
    string lado)
{
    if (actual == nullptr)
        return;

    cout << prefijo
         << "|-- "
         << lado
         << ": "
         << actual->getNombre()
         << " ("
         << actual->getFrecuencia()
         << ")"
         << endl;

    string nuevoPrefijo = prefijo + "    ";

    if (actual->getIzquierdo() != nullptr)
    {
        mostrarArbolRec(actual->getIzquierdo(), nuevoPrefijo, "Izq");
    }

    if (actual->getDerecho() != nullptr)
    {
        mostrarArbolRec(actual->getDerecho(), nuevoPrefijo, "Der");
    }
}

Diagnostico *ArbolAVLDiagnosticos::buscar(string nombre)
{
    return buscarRec(raiz, nombre);
}

Diagnostico *ArbolAVLDiagnosticos::buscarRec(Diagnostico *actual, string nombre)
{
    if (actual == nullptr)
        return nullptr;

    if (actual->getNombre() == nombre)
        return actual;

    Diagnostico *encontrado = buscarRec(actual->getIzquierdo(), nombre);

    if (encontrado != nullptr)
        return encontrado;

    return buscarRec(actual->getDerecho(), nombre);
}

Diagnostico *ArbolAVLDiagnosticos::minimo(Diagnostico *actual)
{
    while (actual != nullptr && actual->getIzquierdo() != nullptr)
    {
        actual = actual->getIzquierdo();
    }

    return actual;
}

Diagnostico *ArbolAVLDiagnosticos::balancear(Diagnostico *actual)
{
    if (actual == nullptr)
        return nullptr;

    int balance = factorBalance(actual);

    if (balance > 1)
    {
        if (factorBalance(actual->getIzquierdo()) < 0)
        {
            actual->setIzquierdo(rotarIzquierda(actual->getIzquierdo()));
        }

        return rotarDerecha(actual);
    }

    if (balance < -1)
    {
        if (factorBalance(actual->getDerecho()) > 0)
        {
            actual->setDerecho(rotarDerecha(actual->getDerecho()));
        }

        return rotarIzquierda(actual);
    }

    return actual;
}

void ArbolAVLDiagnosticos::eliminar(string nombre)
{
    raiz = eliminarRec(raiz, nombre);
}

Diagnostico *ArbolAVLDiagnosticos::eliminarRec(Diagnostico *actual, string nombre)
{
    if (actual == nullptr)
        return nullptr;

    if (actual->getNombre() == nombre)
    {
        if (actual->getIzquierdo() == nullptr && actual->getDerecho() == nullptr)
        {
            delete actual;
            return nullptr;
        }

        if (actual->getIzquierdo() == nullptr)
        {
            Diagnostico *derecho = actual->getDerecho();
            delete actual;
            return derecho;
        }

        if (actual->getDerecho() == nullptr)
        {
            Diagnostico *izquierdo = actual->getIzquierdo();
            delete actual;
            return izquierdo;
        }

        Diagnostico *sucesor = minimo(actual->getDerecho());

        actual->setNombre(sucesor->getNombre());
        actual->setFrecuencia(sucesor->getFrecuencia());

        actual->setDerecho(eliminarRec(actual->getDerecho(), sucesor->getNombre()));
    }
    else
    {
        actual->setIzquierdo(eliminarRec(actual->getIzquierdo(), nombre));
        actual->setDerecho(eliminarRec(actual->getDerecho(), nombre));
    }

    return balancear(actual);
}

void ArbolAVLDiagnosticos::incrementarFrecuencia(string nombre)
{
    Diagnostico *encontrado = buscar(nombre);

    if (encontrado == nullptr)
    {
        cout << "No existe el diagnostico " << nombre << " en el AVL." << endl;
        return;
    }

    string nombreDiagnostico = encontrado->getNombre();
    int nuevaFrecuencia = encontrado->getFrecuencia() + 1;

    eliminar(nombreDiagnostico);

    Diagnostico *actualizado = new Diagnostico(nombreDiagnostico, nuevaFrecuencia);

    insertar(actualizado);
}