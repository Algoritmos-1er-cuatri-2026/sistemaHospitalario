#ifndef SORT_H
#define SORT_H

#include <cstddef>
#include <utility>
#include <vector>

namespace SortUtils
{
    // Realiza la particion del arreglo segun un criterio de orden definido externamente.
    // Devuelve la posicion final del pivote luego de reorganizar los elementos.
    template <typename T, typename Compare>
    std::size_t particion(std::vector<T> &elementos, std::size_t inicio, std::size_t fin, Compare comparar)
    {
        T pivote = elementos[fin];
        std::size_t indiceMenores = inicio;

        for (std::size_t i = inicio; i < fin; i++)
        {
            if (comparar(elementos[i], pivote))
            {
                std::swap(elementos[i], elementos[indiceMenores]);
                indiceMenores++;
            }
        }

        std::swap(elementos[indiceMenores], elementos[fin]);
        return indiceMenores;
    }

    // Aplica QuickSort de manera recursiva sobre el rango indicado.
    // El ordenamiento se define a traves de un comparador, lo que permite reutilizar el algoritmo con distintos tipos.
    template <typename T, typename Compare>
    void quickSort(std::vector<T> &elementos, std::size_t inicio, std::size_t fin, Compare comparar)
    {
        if (elementos.empty() || inicio >= fin)
        {
            return;
        }

        std::size_t indicePivote = particion(elementos, inicio, fin, comparar);

        if (indicePivote > 0)
        {
            quickSort(elementos, inicio, indicePivote - 1, comparar);
        }

        quickSort(elementos, indicePivote + 1, fin, comparar);
    }

    // Sobrecarga de conveniencia que ordena toda la secuencia completa.
    template <typename T, typename Compare>
    void quickSort(std::vector<T> &elementos, Compare comparar)
    {
        if (elementos.empty())
        {
            return;
        }

        quickSort(elementos, 0, elementos.size() - 1, comparar);
    }
}

/*
Uso sugerido del modulo de ordenamiento:

1. Para Ambulancia:

    #include "Sort.h"

    vector<Insumo> insumosOrdenados = listaInsumos;
    SortUtils::quickSort(insumosOrdenados, [](const Insumo &izquierdo, const Insumo &derecho)
    {
        float relacionIzquierda = izquierdo.getPesoKg() > 0.0f
            ? static_cast<float>(izquierdo.getValorClinico()) / izquierdo.getPesoKg()
            : static_cast<float>(izquierdo.getValorClinico());

        float relacionDerecha = derecho.getPesoKg() > 0.0f
            ? static_cast<float>(derecho.getValorClinico()) / derecho.getPesoKg()
            : static_cast<float>(derecho.getValorClinico());

        if (relacionIzquierda == relacionDerecha)
        {
            return izquierdo.getValorClinico() > derecho.getValorClinico();
        }

        return relacionIzquierda > relacionDerecha;
    });

2. Para SistemaHospitalario:

    #include "Sort.h"

    vector<Hospital> hospitalesOrdenados = listaHospitales;
    SortUtils::quickSort(hospitalesOrdenados, [criterio](const Hospital &izquierdo, const Hospital &derecho)
    {
        if (criterio == 1) return izquierdo.getCapacidad() > derecho.getCapacidad();
        if (criterio == 2) return izquierdo.getPersonal() > derecho.getPersonal();
        if (criterio == 3) return izquierdo.getPresupuesto() > derecho.getPresupuesto();
        return false;
    });

Observacion:
La version generica recibe un comparador, por lo que puede adaptarse a distintos tipos de datos sin modificar el algoritmo.
*/

#endif