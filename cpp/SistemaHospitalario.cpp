#include "../header/SistemaHospitalario.h"
#include <iostream>
#include <queue> 

using namespace std;


void SistemaHospitalario::mostrarInformacionDeHospital(string codigo) { //PUNTO 1.
    for(int i = 0; i < listaHospitales.size(); i++) {
        if (this->listaHospitales[i].getCodigo() == codigo){
            listaHospitales[i].mostrarInformacion();
            return;
        }
    }
    cout<<"No existe el hospital ingresado \n";
}

void SistemaHospitalario::registrarHospital(Hospital nuevoHospital) {
    this->listaHospitales.push_back(nuevoHospital);
}

void SistemaHospitalario::eliminarHospital(string codigo) {
    int indice = obtenerIndice(codigo);

    if (indice == -1) {
        cout << "Error: El hospital con codigo " << codigo << " no existe." << endl;
        return;
    }

    this->listaHospitales.erase(this->listaHospitales.begin() + indice);
}

void SistemaHospitalario::registrarDerivacion(Derivacion nuevaDerivacion) {
    this->listaDerivaciones.push_back(nuevaDerivacion);
}

int SistemaHospitalario::obtenerIndice(string codigo) {
    for (size_t i = 0; i < this->listaHospitales.size(); i++) { 
        if (this->listaHospitales[i].getCodigo() == codigo) return i;
    }
    return -1; 
}

vector<Hospital> SistemaHospitalario::mostrarLista(){
    return this->listaHospitales;
}

// Ordenamiento de la lista según filtro

//Elegimos Quicksort, porque es el algoritmo más rápido, ordena los elementos sin crear subarreglos como mergesort, lo que ahorra memoria.

// 1 = capacidad de camas . 2 = cantidad de personal médico .  3 = presupuesto anual

bool esMayor(Hospital a, Hospital b, int criterio) {
    if (criterio == 1) return a.getCapacidad() > b.getCapacidad();
    if (criterio == 2) return a.getPersonal() > b.getPersonal();
    if (criterio == 3) return a.getPresupuesto() > b.getPresupuesto();
    return false;
}


int particion(vector<Hospital>& arr, int inicio, int fin, int criterio) {
    Hospital pivote = arr[fin]; // Elegimos el último elemento como pivote
    int i = inicio - 1; // marca la zona donde se terminan los hospitales mayores al pivote

    for (int j = inicio; j < fin; j++) {
        if (esMayor(arr[j], pivote, criterio)) { // Si el hospital que estamos analizando, es mayor que el pivote lo posicionamos a la izquierda.
            i++;
            Hospital temp = arr[i]; 
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
   
    Hospital temp = arr[i + 1];  
    arr[i + 1] = arr[fin];// Colocamos el pivote en la posición que va, a la derecha de los mayores e izquierda de los menores a él
    arr[fin] = temp;

    return i + 1; 
}

void quickSort(vector<Hospital>& arr, int inicio, int fin, int criterio) {
    if (inicio < fin) {
        int indicePivote = particion(arr, inicio, fin, criterio);
        
        quickSort(arr, inicio, indicePivote - 1, criterio); //Izquierda
        quickSort(arr, indicePivote + 1, fin, criterio); //Derecha
    }
}

vector<Hospital> SistemaHospitalario::listarHospitales(int criterio) {
    vector<Hospital> listaOrdenada = this->listaHospitales; 
    
   quickSort(listaOrdenada, 0, listaOrdenada.size() - 1, criterio);
    
    return listaOrdenada;
}

// EJERCICIO DERIVACIÓN CON DIJKSTRA: 

void SistemaHospitalario::agregarDerivacion(Derivacion d) {
    this->listaDerivaciones.push_back(d);
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

//Implementación dijkstra:


cout<<"Calculando ruta entre "<<origen<<" y "<<destino<<endl;

const int INF = 99999;
    int n = listaHospitales.size();

    vector<int> distancia(n, INF);
    vector<bool> visitado(n, false);
    vector<int> padre(n, -1); 

   
    distancia[indiceOrigen] = 0;

    
    for (int i = 0; i < n - 1; i++) {
        
        int min_distancia = INF;
        int u = -1;

        for (int v = 0; v < n; v++) {
            if (!visitado[v] && distancia[v] < min_distancia) {
                min_distancia = distancia[v];
                u = v;
            }
        }

        
        if (u == -1 || distancia[u] == INF) {
            break;
        }

        
        visitado[u] = true;

        
        if (u == indiceDestino) {
            break;
        }

       
        for (int v = 0; v < n; v++) {
            
            if (!visitado[v] && grafo[u][v] != INF && distancia[u] + grafo[u][v] < distancia[v]) {
                distancia[v] = distancia[u] + grafo[u][v];
                padre[v] = u; 
            }
        }
    }

   
    if (distancia[indiceDestino] == INF) {
        cout << "No existe una ruta de derivación disponible entre " << origen << " y " << destino << "." << endl;
    } else {
        cout << "\n Camino minimo encontrado: " << endl;
        cout << "Tiempo total de traslado: " << distancia[indiceDestino] << " minutos." << endl;

        
        vector<int> camino;
        int actual = indiceDestino;
        while (actual != -1) {
            camino.push_back(actual);
            actual = padre[actual];
        }

        
        cout << "Ruta a seguir: ";
        for (int i = camino.size() - 1; i >= 0; i--) {
            int idx = camino[i];
            
            cout << listaHospitales[idx].getCodigo(); 
            
            if (i > 0) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

void SistemaHospitalario::buscarPorEspecialidad(string especialidad) {
    vector<Hospital> hospitalesFiltrados;

    for (Hospital h : this->listaHospitales) {
        if (h.tieneEspecialidad(especialidad)) {
            hospitalesFiltrados.push_back(h);
        }
    }
    
    if (hospitalesFiltrados.empty()) {
        cout << "No se encontraron hospitales con la especialidad: " << especialidad << endl;
        return;
    }

    //ordenamos reutilizando el quicskort del punto 4 ya que el criterio 1 era camas.

    quickSort(hospitalesFiltrados,0,hospitalesFiltrados.size()-1,1);

    cout << "\n--- Hospitales con especialidad en " << especialidad << " ---" << endl;
    for (Hospital h : hospitalesFiltrados) {
        cout << "Hospital: " << h.getCodigo() << " | Camas disponibles: " << h.getCapacidad() << " | Especialidades totales : " << h.getEspecialidades() << endl;
    }
}

