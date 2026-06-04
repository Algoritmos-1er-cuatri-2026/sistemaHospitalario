#ifndef DERIVACION_H
#define DERIVACION_H

#include <vector>
#include "Insumo.h"
using namespace std;

class Derivacion {
private:
    string hospitalOrigen;
    string hospitalDestino;
    int tiempoMinutos;

public:
    Derivacion(string origen, string destino, int tiempo);

    string getOrigen();
    string getDestino();
    int getTiempo();

    vector<Insumo*> optimizarCarga(vector<Insumo*> listaInsumos);
};

#endif