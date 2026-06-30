#ifndef INSUMO_H
#define INSUMO_H

#include <vector>
#include <string>
using namespace std;

class Insumo
{
private:
    string nombre;
    float pesoKg;
    int valorClinico;

public:
    Insumo();
    Insumo(string nombre, float pesoKg, int valorClinico);

    string getNombre() const;
    float getPesoKg() const;
    int getValorClinico() const;

    void setNombre(string nombre);
    void setPesoKg(float pesoKg);
    void setValorClinico(int valorClinico);

    static vector<Insumo> leerDesdeArchivo(const string &rutaArchivo = "datos/insumos.txt");
    static bool guardarEnArchivo(const vector<Insumo> &insumos, const string &rutaArchivo = "datos/insumos.txt");
};

#endif