#ifndef INSUMO_H
#define INSUMO_H

#include <vector>
#include <string>
using namespace std;

class Insumo
{
private:
    int idInsumo;
    string nombre;
    float pesoKg;
    int valorClinico;

public:
    Insumo();
    Insumo(int idInsumo, string nombre, float pesoKg, int valorClinico);

    int getIdInsumo() const;
    string getNombre() const;
    float getPesoKg() const;
    int getValorClinico() const;

    void setIdInsumo(int idInsumo);
    void setNombre(string nombre);
    void setPesoKg(float pesoKg);
    void setValorClinico(int valorClinico);
};

#endif