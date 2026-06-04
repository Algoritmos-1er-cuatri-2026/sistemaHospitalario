#include "SistemaHospitalario.h"
#include <iostream>
#include <queue> 

using namespace std;

int SistemaHospitalario::obtenerIndice(string codigo) {
    for (size_t i = 0; i < this->listaHospitales.size(); i++) { 
        if (this->listaHospitales[i].getCodigo() == codigo) return i;
    }
    return -1; 
}

vector<Hospital> SistemaHospitalario::mostrarLista(){
    return this->listaHospitales;
}

void SistemaHospitalario::calcularRutaMasRapida(string origen, string destino) {
    int indiceOrigen = obtenerIndice(origen);
    int indiceDestino = obtenerIndice(destino);
    
    if (indiceOrigen == -1 || indiceDestino == -1) {
        cout << "Error: Hospital no valido" << endl;
        return;
    }
    
    vector<vector<int>> grafo(
    listaHospitales.size(),
    vector<int>(listaHospitales.size(), 99999)
    );

    for(int i = 0; i < listaHospitales.size(); i++) {
    grafo[i][i] = 0;
    }

    for (Derivacion d : this->listaDerivaciones) {
    int DerOrigen = obtenerIndice(d.getOrigen());
    int DerDestino = obtenerIndice(d.getDestino());

    if(DerOrigen != -1 && DerDestino != -1) {
        grafo[DerOrigen][DerDestino] = d.getTiempo();
        grafo[DerDestino][DerOrigen] = d.getTiempo();
    }
}

cout << "Grafo de derivaciones";

for(int i = 0; i < grafo.size(); i++)
{
    for(int j = 0; j < grafo[i].size(); j++)
    {
        cout << grafo[i][j] <<"\t";
    }
    cout << endl;
}

// crear dijkstra


cout<<"Calculando ruta entre "<<origen<<" y "<<destino<<endl;

}

