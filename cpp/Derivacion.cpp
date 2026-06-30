#include "../header/Derivacion.h"

Derivacion::Derivacion(string origen, string destino, int tiempo) {
    this->hospitalOrigen = origen;
    this->hospitalDestino = destino;
    this->tiempoMinutos = tiempo;
}

string Derivacion::getOrigen() {
    return this->hospitalOrigen;
}

string Derivacion::getDestino() {
    return this->hospitalDestino;
}

int Derivacion::getTiempo() {
    return this->tiempoMinutos;
}

vector<Insumo*> Derivacion::optimizarCarga(vector<Insumo*> listaInsumos) {
    vector<Insumo*> cargaOptima;
    
    // Recorri listaInsumos para desaparecer el Warning
    for (size_t i = 0; i < listaInsumos.size(); i++) {
    }

    
    return cargaOptima;
}