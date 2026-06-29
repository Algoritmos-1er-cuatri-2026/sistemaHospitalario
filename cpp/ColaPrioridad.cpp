#include "../header/ColaPrioridad.h"
#include <stdexcept>

ColaPrioridad::ColaPrioridad() {}

bool ColaPrioridad::esVacia() {
    return heap.empty();
}

bool ColaPrioridad::tieneMayorPrioridad(Paciente p1, Paciente p2) {
    if (p1.getPrioridad() < p2.getPrioridad()) return true;
    if (p1.getPrioridad() == p2.getPrioridad()) {
        return p1.getFechaIngreso() < p2.getFechaIngreso();
    }
    return false;
}

void ColaPrioridad::flotar(int indice) {
    while (indice > 0) {
        int padre = (indice - 1) / 2;
        if (tieneMayorPrioridad(heap[indice], heap[padre])) {
            std::swap(heap[indice], heap[padre]);
            indice = padre;
        } else {
            break;
        }
    }
}

void ColaPrioridad::hundir(int indice) {
    int tamano = heap.size();
    while (2 * indice + 1 < tamano) {
        int hijoIzquierdo = 2 * indice + 1;
        int hijoDerecho = 2 * indice + 2;
        int hijoMasPrioritario = hijoIzquierdo;

        if (hijoDerecho < tamano && tieneMayorPrioridad(heap[hijoDerecho], heap[hijoIzquierdo])) {
            hijoMasPrioritario = hijoDerecho;
        }

        if (tieneMayorPrioridad(heap[hijoMasPrioritario], heap[indice])) {
            std::swap(heap[indice], heap[hijoMasPrioritario]);
            indice = hijoMasPrioritario;
        } else {
            break;
        }
    }
}

void ColaPrioridad::encolar(Paciente p) {
    heap.push_back(p);
    flotar(heap.size() - 1);
}

Paciente ColaPrioridad::desencolar() {
    if (esVacia()) {
        throw std::runtime_error("Cola vacia");
    }
    Paciente raiz = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) {
        hundir(0);
    }
    return raiz;
}

void ColaPrioridad::actualizarPrioridad(int idPaciente, int nuevaPrioridad) {
    for (size_t i = 0; i < heap.size(); i++) {
        if (heap[i].getIdPaciente() == idPaciente) {
            int viejaPrioridad = heap[i].getPrioridad();
            heap[i].setPrioridad(nuevaPrioridad);
            if (nuevaPrioridad < viejaPrioridad) {
                flotar(i);
            } else {
                hundir(i);
            }
            return;
        }
    }
}