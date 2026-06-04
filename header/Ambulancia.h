#ifndef AMBULANCIA_H
#define AMBULANCIA_H

#include <vector>
#include <string>
#include "Insumo.h"
using namespace std;

class Ambulancia
{
private:
    int idAmbulancia;
    float capacidad;

public:
    bool quedaLugar();
    void agregarInsumo(Insumo unInsumo);
};

#endif