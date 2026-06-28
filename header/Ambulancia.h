#ifndef AMBULANCIA_H
#define AMBULANCIA_H

#include <cstddef>
#include <vector>
#include <string>
#include "Insumo.h"
using namespace std;

class Ambulancia
{
public:
    struct ResultadoOptimizacion
    {
        vector<Insumo> insumosSeleccionados;
        int valorTotal;
        float pesoTotal;
        long long nodosExplorados;

        ResultadoOptimizacion();
    };

private:
    int idAmbulancia;
    float capacidad;
    vector<Insumo> cargaActual;

    static bool compararPorRelacionValorPeso(const Insumo &primerInsumo, const Insumo &segundoInsumo);

    void actualizarMejorCarga(const vector<Insumo> &seleccionActual, float pesoActual, int valorActual, ResultadoOptimizacion &mejorResultado) const;

    void backtrackingPuroRec(const vector<Insumo> &listaInsumos, size_t indice, float pesoActual, int valorActual, vector<Insumo> &seleccionActual, ResultadoOptimizacion &mejorResultado, long long &nodosExplorados) const;

    double calcularCotaSuperior(const vector<Insumo> &listaInsumosOrdenada, size_t indice, float pesoActual, int valorActual) const;

    void branchAndBoundRec(const vector<Insumo> &listaInsumosOrdenada, size_t indice, float pesoActual, int valorActual, vector<Insumo> &seleccionActual, ResultadoOptimizacion &mejorResultado, long long &nodosExplorados) const;

public:
    Ambulancia();
    Ambulancia(int idAmbulancia, float capacidad);

    int getIdAmbulancia() const;
    float getCapacidad() const;
    float getPesoCargado() const;
    const vector<Insumo> &getCarga() const;

    bool quedaLugar() const;
    void agregarInsumo(Insumo unInsumo);

    ResultadoOptimizacion resolverBacktrackingPuro(const vector<Insumo> &listaInsumos) const;
    ResultadoOptimizacion resolverBranchAndBound(const vector<Insumo> &listaInsumos) const;
};

#endif