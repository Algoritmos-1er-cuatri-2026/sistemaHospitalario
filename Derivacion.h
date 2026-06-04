#ifndef DERIVACION_H
#define DERIVACION_H

#include <vector>
#include <Insumo.h>
using namespace std;

class Derivacion
{
private:
    int tiempoMinutos;

public:

vector<Insumo *>optimizarCarga(vector<Insumo *> listaInsumos);
};

#endif