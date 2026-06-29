#include "../header/ArbolDeDiagnosticos.h"
#include <iostream>

using namespace std;

ArbolDeDiagnosticos::ArbolDeDiagnosticos()
{
    raiz = nullptr;
}

ArbolDeDiagnosticos::~ArbolDeDiagnosticos()
{
    destruirRec(raiz);
    raiz = nullptr;
}

void ArbolDeDiagnosticos::destruirRec(Diagnostico* actual)
{
    if (actual == nullptr)
        return;

    destruirRec(actual->getIzquierdo());
    destruirRec(actual->getDerecho());

    delete actual;
}

bool ArbolDeDiagnosticos::estaVacio()
{
    return raiz == nullptr;
}

bool ArbolDeDiagnosticos::esMenor(Diagnostico *primero, Diagnostico *segundo)
{
    if (primero->getFrecuencia() < segundo->getFrecuencia())
        return true;

    if (primero->getFrecuencia() > segundo->getFrecuencia())
        return false;

    return primero->getNombre() < segundo->getNombre();
}

void ArbolDeDiagnosticos::insertar(Diagnostico *diagnostico)
{
    if (diagnostico == nullptr)
        return;

    diagnostico->setIzquierdo(nullptr);
    diagnostico->setDerecho(nullptr);

    raiz = insertarRec(raiz, diagnostico);
}

Diagnostico *ArbolDeDiagnosticos::insertarRec(Diagnostico *actual, Diagnostico *nuevo)
{
    if (actual == nullptr)
        return nuevo;

    if (esMenor(nuevo, actual))
        actual->setIzquierdo(insertarRec(actual->getIzquierdo(), nuevo));
    else
        actual->setDerecho(insertarRec(actual->getDerecho(), nuevo));

    return actual;
}

Diagnostico *ArbolDeDiagnosticos::buscar(string nombre)
{
    return buscarRec(raiz, nombre);
}

Diagnostico *ArbolDeDiagnosticos::buscarRec(Diagnostico *actual, string nombre)
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

void ArbolDeDiagnosticos::incrementarFrecuencia(string nombre)
{
    Diagnostico *diagnostico = buscar(nombre);

    if (diagnostico == nullptr)
    {
        cout << "No existe el diagnostico " << nombre << "." << endl;
        return;
    }

    raiz = eliminarNodoRec(raiz, diagnostico);

    diagnostico->incrementarFrecuencia();
    diagnostico->setIzquierdo(nullptr);
    diagnostico->setDerecho(nullptr);

    insertar(diagnostico);
}

void ArbolDeDiagnosticos::listarDiagnosticos()
{
    if (raiz == nullptr)
    {
        cout << "No hay diagnosticos cargados." << endl;
        return;
    }

    inorderRec(raiz);
}

void ArbolDeDiagnosticos::inorderRec(Diagnostico *actual)
{
    if (actual == nullptr)
        return;

    inorderRec(actual->getIzquierdo());

    cout << "Diagnostico: " << actual->getNombre()
         << " | Frecuencia: " << actual->getFrecuencia()
         << endl;

    inorderRec(actual->getDerecho());
}

Diagnostico *ArbolDeDiagnosticos::buscarMayorRec(Diagnostico *actual)
{
    if (actual == nullptr)
        return nullptr;

    while (actual->getDerecho() != nullptr)
        actual = actual->getDerecho();

    return actual;
}

Diagnostico *ArbolDeDiagnosticos::diagnosticoMasFrecuente()
{
    return buscarMayorRec(raiz);
}

void ArbolDeDiagnosticos::eliminar(string nombre)
{
    Diagnostico *diagnostico = buscar(nombre);

    if (diagnostico == nullptr)
    {
        cout << "No existe el diagnostico " << nombre << "." << endl;
        return;
    }

    raiz = eliminarNodoRec(raiz, diagnostico);
    delete diagnostico;
}

Diagnostico *ArbolDeDiagnosticos::eliminarNodoRec(Diagnostico *actual, Diagnostico *objetivo)
{
    if (actual == nullptr)
        return nullptr;

    if (actual == objetivo)
    {
        Diagnostico *izquierdo = actual->getIzquierdo();
        Diagnostico *derecho = actual->getDerecho();

        actual->setIzquierdo(nullptr);
        actual->setDerecho(nullptr);

        if (izquierdo == nullptr)
            return derecho;

        if (derecho == nullptr)
            return izquierdo;

        Diagnostico *sucesor = nullptr;
        derecho = extraerMinimo(derecho, sucesor);

        sucesor->setIzquierdo(izquierdo);
        sucesor->setDerecho(derecho);

        return sucesor;
    }

    if (esMenor(objetivo, actual))
        actual->setIzquierdo(eliminarNodoRec(actual->getIzquierdo(), objetivo));
    else
        actual->setDerecho(eliminarNodoRec(actual->getDerecho(), objetivo));

    return actual;
}

Diagnostico *ArbolDeDiagnosticos::extraerMinimo(Diagnostico *actual, Diagnostico *&minimoExtraido)
{
    if (actual->getIzquierdo() == nullptr)
    {
        minimoExtraido = actual;
        return actual->getDerecho();
    }

    actual->setIzquierdo(extraerMinimo(actual->getIzquierdo(), minimoExtraido));
    return actual;
}

int ArbolDeDiagnosticos::altura()
{
    return alturaRec(raiz);
}

int ArbolDeDiagnosticos::alturaRec(Diagnostico *actual)
{
    if (actual == nullptr)
        return -1;

    int alturaIzquierda = alturaRec(actual->getIzquierdo());
    int alturaDerecha = alturaRec(actual->getDerecho());

    if (alturaIzquierda > alturaDerecha)
        return alturaIzquierda + 1;

    return alturaDerecha + 1;
}

bool ArbolDeDiagnosticos::estaDesbalanceado()
{
    return estaDesbalanceadoRec(raiz);
}

bool ArbolDeDiagnosticos::estaDesbalanceadoRec(Diagnostico *actual)
{
    if (actual == nullptr)
        return false;

    int izquierda = alturaRec(actual->getIzquierdo());
    int derecha = alturaRec(actual->getDerecho());

    int diferencia = izquierda - derecha;

    if (diferencia < 0)
        diferencia = diferencia * -1;

    if (diferencia > 2)
        return true;

    return estaDesbalanceadoRec(actual->getIzquierdo()) ||
           estaDesbalanceadoRec(actual->getDerecho());
}

void ArbolDeDiagnosticos::mostrarArbol()
{
    if (raiz == nullptr)
    {
        cout << "No hay diagnosticos cargados." << endl;
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
        mostrarArbolRec(
            raiz->getIzquierdo(),
            "",
            "Izq");
    }

    if (raiz->getDerecho() != nullptr)
    {
        mostrarArbolRec(
            raiz->getDerecho(),
            "",
            "Der");
    }
}

void ArbolDeDiagnosticos::mostrarArbolRec(
    Diagnostico *actual,
    string prefijo,
    string lado)
{
    if (actual == nullptr)
        return;

    cout << prefijo;

    cout << prefijo << "|-- ";

    cout << lado
         << ": "
         << actual->getNombre()
         << " ("
         << actual->getFrecuencia()
         << ")"
         << endl;

    string nuevoPrefijo = prefijo + "    ";

    bool tieneIzq = actual->getIzquierdo() != nullptr;
    bool tieneDer = actual->getDerecho() != nullptr;

    if (tieneIzq)
    {
        mostrarArbolRec(
            actual->getIzquierdo(),
            nuevoPrefijo,
            "Izq");
    }

    if (tieneDer)
    {
        mostrarArbolRec(
            actual->getDerecho(),
            nuevoPrefijo,
            "Der");
    }
}