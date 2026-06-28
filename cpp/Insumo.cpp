#include "../header/Insumo.h"

Insumo::Insumo()
{
    this->idInsumo = 0;
    this->nombre = "";
    this->pesoKg = 0.0f;
    this->valorClinico = 0;
}

Insumo::Insumo(int idInsumo, string nombre, float pesoKg, int valorClinico)
{
    this->idInsumo = idInsumo;
    this->nombre = nombre;
    this->pesoKg = pesoKg;
    this->valorClinico = valorClinico;
}

//Getters
int Insumo::getIdInsumo() const
{
    return this->idInsumo;
}

string Insumo::getNombre() const
{
    return this->nombre;
}

float Insumo::getPesoKg() const
{
    return this->pesoKg;
}

int Insumo::getValorClinico() const
{
    return this->valorClinico;
}

//Setters, no veo que sean necesarios, pero los pongo igual
void Insumo::setIdInsumo(int idInsumo)
{
    this->idInsumo = idInsumo;
}

void Insumo::setNombre(string nombre)
{
    this->nombre = nombre;
}

void Insumo::setPesoKg(float pesoKg)
{
    this->pesoKg = pesoKg;
}

void Insumo::setValorClinico(int valorClinico)
{
    this->valorClinico = valorClinico;
}