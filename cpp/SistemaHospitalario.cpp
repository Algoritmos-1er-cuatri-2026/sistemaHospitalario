#include "../header/SistemaHospitalario.h"
#include "../header/ColaPrioridad.h"
#include "../header/Sort.h"
#include <iostream>
#include <queue>

using namespace std;

void SistemaHospitalario::mostrarInformacionDeHospital(string codigo)
{ 
    int indice = obtenerIndice(codigo);
    if (indice == -1)
    {
        cout<<"El codigo ingresado no corresponde a un hospital valido";
        return;
    }
    this->listaHospitales[indice].mostrarInformacion();
    
}

void SistemaHospitalario::registrarHospital(Hospital nuevoHospital)
{
    this->listaHospitales.push_back(nuevoHospital);
    inicializarTablaHash();
}

string SistemaHospitalario::obtenerHospitalMasCercano(string codigoOrigen)
{
    int indiceOrigen = obtenerIndice(codigoOrigen);
    if (indiceOrigen == -1)
        return "";
    int cantidadHospitales = listaHospitales.size();
    vector<vector<int>> grafo = this->construirGrafoMatriz();

    vector<int> distancia;
    vector<int> padre;
    ejecutarDijkstra(indiceOrigen, grafo, distancia, padre);

    const int INF = 99999;
    int menorTiempo = INF;
    int indiceMasCercano = -1;

    for (int i = 0; i < cantidadHospitales; i++)
    {
        if (i != indiceOrigen && distancia[i] > 0 && distancia[i] < menorTiempo)
        {
            menorTiempo = distancia[i];
            indiceMasCercano = i;
        }
    }

    if (indiceMasCercano != -1)
    {
        return listaHospitales[indiceMasCercano].getCodigo();
    }
    return "";
}

void SistemaHospitalario::eliminarHospital(string codigo)
{
    int indice = obtenerIndice(codigo);

    if (indice == -1)
    {
        cout << "Error: El hospital con codigo " << codigo << " no existe." << endl;
        return;
    }

    string codigoMasCercano = obtenerHospitalMasCercano(codigo);
    if (codigoMasCercano != "")
    {
        cout << "Derivando pacientes desde " << codigo << " hasta " << codigoMasCercano << endl;

        for (size_t i = 0; i < this->listaPacientes.size(); i++)
        {
            if (this->listaPacientes[i].getCodHospital() == codigo)
            {
                this->listaPacientes[i].setCodHospital(codigoMasCercano);
            }
        }
    }
    this->listaHospitales.erase(this->listaHospitales.begin() + indice);
    inicializarTablaHash();
}

void SistemaHospitalario::mostrarPacientes()
{
    for (size_t i = 0; i < this->listaPacientes.size(); i++)
    {
        cout << "Hospital: " << this->listaPacientes[i].getCodHospital()
             << " | ID Paciente: " << this->listaPacientes[i].getIdPaciente()
             << " | DNI: " << this->listaPacientes[i].getDni()
             << " | Fecha de ingreso: " << this->listaPacientes[i].getFechaIngreso()
             << " | Diagnostico: " << this->listaPacientes[i].getDiagnostico()
             << " | Prioridad: " << this->listaPacientes[i].getPrioridad()
             << " | Peso en KG: " << this->listaPacientes[i].getKg() << endl;
    }
}

void SistemaHospitalario::registrarDerivacion(Derivacion nuevaDerivacion)
{
    this->listaDerivaciones.push_back(nuevaDerivacion);
}

// HASH

bool SistemaHospitalario::esPrimo(int numero)
{
    if (numero <= 1)
        return false;
    for (int i = 2; i * i <= numero; i++)
    {
        if (numero % i == 0)
            return false;
    }
    return true;
}

int SistemaHospitalario::proximoPrimo(int numero)
{
    while (!esPrimo(numero))
    {
        numero++;
    }
    return numero;
}

int SistemaHospitalario::calcularHash(string codigo)
{
    int sumaAscii = 0;

    for (size_t i = 0; i < codigo.length(); i++)
    {
        sumaAscii += codigo[i];
    }

    return sumaAscii % this->tamanoTablaHash;
}

void SistemaHospitalario::inicializarTablaHash()
{
    size_t cantidadElementos = this->listaHospitales.size();
    if (cantidadElementos == 0)
    {
        this->tamanoTablaHash = 0;
        this->tablaHash.clear();
        return;
    }

    this->tamanoTablaHash = proximoPrimo(cantidadElementos / 0.8);

    this->tablaHash.clear();
    this->tablaHash.resize(this->tamanoTablaHash, NodoHash());

    for (size_t i = 0; i < cantidadElementos; i++)
    {
        string cod = this->listaHospitales[i].getCodigo();
        int pos = calcularHash(cod);

        // Elegimos linear probing ante casos de colisiones
        while (this->tablaHash[pos].estado == OCUPADO)
        {
            pos = (pos + 1) % this->tamanoTablaHash;
        }

        this->tablaHash[pos].codigo = cod;
        this->tablaHash[pos].indiceVector = i;
        this->tablaHash[pos].estado = OCUPADO;
    }
}

int SistemaHospitalario::obtenerIndice(string codigo)
{
    int posicion = calcularHash(codigo);
    int posicionInicial = posicion;

    while (this->tablaHash[posicion].estado != LIBRE)
    {
        if (this->tablaHash[posicion].codigo == codigo)
        {
            return this->tablaHash[posicion].indiceVector;
        }
        posicion = (posicion + 1) % this->tamanoTablaHash;
        if (posicion == posicionInicial)
            break;
    }
    return -1;
}

vector<Hospital> SistemaHospitalario::mostrarLista()
{
    return this->listaHospitales;
}

// Ordenamiento de la lista según filtro

// Elegimos Quicksort, porque es el algoritmo más rápido, ordena los elementos sin crear subarreglos como mergesort, lo que ahorra memoria.

// 1 = capacidad de camas . 2 = cantidad de personal médico .  3 = presupuesto anual

bool esMayor(Hospital a, Hospital b, int criterio)
{
    if (criterio == 1)
        return a.getCapacidad() > b.getCapacidad();
    if (criterio == 2)
        return a.getPersonal() > b.getPersonal();
    if (criterio == 3)
        return a.getPresupuesto() > b.getPresupuesto();
    return false;
}

int particion(Hospital* arr, int inicio, int fin, int criterio)
{
    Hospital pivote = arr[fin]; // Elegimos el último elemento como pivote
    int i = inicio - 1;         // marca la zona donde se terminan los hospitales mayores al pivote

    for (int j = inicio; j < fin; j++)
    {
        if (esMayor(arr[j], pivote, criterio))
        { // Si el hospital que estamos analizando, es mayor que el pivote lo posicionamos a la izquierda.
            i++;
            Hospital temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    Hospital temp = arr[i + 1];
    arr[i + 1] = arr[fin]; // Colocamos el pivote en la posición que va, a la derecha de los mayores e izquierda de los menores a él
    arr[fin] = temp;

    return i + 1;
}

void quickSort(Hospital* arr, int inicio, int fin, int criterio)
{
    if (inicio < fin)
    {
        int indicePivote = particion(arr, inicio, fin, criterio);

        quickSort(arr, inicio, indicePivote - 1, criterio); // Izquierda
        quickSort(arr, indicePivote + 1, fin, criterio);    // Derecha
    }
}

void SistemaHospitalario::listarHospitales(int criterio)
{

    int cantidadHospitales = this->listaHospitales.size();

    Hospital* vectorHeap = new Hospital[cantidadHospitales];

    for (int i = 0; i < cantidadHospitales; i++)
    {
        vectorHeap[i] = this->listaHospitales[i];
    }

    quickSort(vectorHeap,0,cantidadHospitales-1,criterio);
   
    for (int i = 0; i < cantidadHospitales; i++)
                    {
                        cout << i + 1 << ". Codigo: " << vectorHeap[i].getCodigo();
                        cout << " | Camas: " << vectorHeap[i].getCapacidad();
                        cout << " | Personal: " << vectorHeap[i].getPersonal();
                        cout << " | Presupuesto: $" << vectorHeap[i].getPresupuesto() << endl;
                    }
    delete[] vectorHeap;
}

// DIJKSTRA

void SistemaHospitalario::agregarDerivacion(Derivacion d)
{
    this->listaDerivaciones.push_back(d);
}

vector<vector<int>> SistemaHospitalario::construirGrafoMatriz()
{
    vector<vector<int>> grafo(
        listaHospitales.size(),
        vector<int>(listaHospitales.size(), 99999));

    for (size_t i = 0; i < listaHospitales.size(); i++)
    {
        grafo[i][i] = 0;
    }

    for (Derivacion d : this->listaDerivaciones)
    {
        int DerOrigen = obtenerIndice(d.getOrigen());
        int DerDestino = obtenerIndice(d.getDestino());

        if (DerOrigen != -1 && DerDestino != -1)
        {
            grafo[DerOrigen][DerDestino] = d.getTiempo();
            grafo[DerDestino][DerOrigen] = d.getTiempo();
        }
    }
    return grafo;
}

void SistemaHospitalario::ejecutarDijkstra(int indiceOrigen, const vector<vector<int>> &grafo, vector<int> &distancia, vector<int> &padre)
{
    const int INF = 99999;
    int n = grafo.size();

    distancia.assign(n, INF);
    padre.assign(n, -1);

    bool* visitado = new bool[n];
    for(int i = 0; i < n; i++) {
        visitado[i] = false;
    }

    distancia[indiceOrigen] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int min_distancia = INF;
        int u = -1;

        for (int v = 0; v < n; v++)
        {
            if (!visitado[v] && distancia[v] < min_distancia)
            {
                min_distancia = distancia[v];
                u = v;
            }
        }

        if (u == -1 || distancia[u] == INF)
        {
            break;
        }

        visitado[u] = true;

        for (int v = 0; v < n; v++)
        {
            if (!visitado[v] && grafo[u][v] != INF && distancia[u] + grafo[u][v] < distancia[v])
            {
                distancia[v] = distancia[u] + grafo[u][v];
                padre[v] = u;
            }
        }
    }
    delete[] visitado;
}

void SistemaHospitalario::calcularRutaMasRapida(string origen, string destino)
{
    int indiceOrigen = obtenerIndice(origen);
    int indiceDestino = obtenerIndice(destino);

    if (indiceOrigen == -1 || indiceDestino == -1)
    {
        cout << "Error: Hospital no valido" << endl;
        return;
    }

    vector<vector<int>> grafo = construirGrafoMatriz();

    cout << "Grafo de derivaciones" << endl;
    for (size_t i = 0; i < grafo.size(); i++)
    {
        for (size_t j = 0; j < grafo[i].size(); j++)
        {
            cout << grafo[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "Calculando ruta entre " << origen << " y " << destino << endl;

    vector<int> distancia;
    vector<int> padre;
    ejecutarDijkstra(indiceOrigen, grafo, distancia, padre);

    const int INF = 99999;
    if (distancia[indiceDestino] == INF)
    {
        cout << "No existe una ruta de derivación disponible entre " << origen << " y " << destino << "." << endl;
    }
    else
    {
        cout << "\n Camino minimo encontrado: " << endl;
        cout << "Tiempo total de traslado: " << distancia[indiceDestino] << " minutos." << endl;

        vector<int> camino;
        int actual = indiceDestino;
        while (actual != -1)
        {
            camino.push_back(actual);
            actual = padre[actual];
        }

        cout << "Ruta a seguir: ";
        for (int i = camino.size() - 1; i >= 0; i--)
        {
            int idx = camino[i];

            cout << listaHospitales[idx].getCodigo();

            if (i > 0)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

void SistemaHospitalario::buscarPorEspecialidad(string especialidad)
{
    vector<Hospital> hospitalesFiltrados;

    for (Hospital h : this->listaHospitales)
    {
        if (h.tieneEspecialidad(especialidad))
        {
            hospitalesFiltrados.push_back(h);
        }
    }

    if (hospitalesFiltrados.empty())
    {
        cout << "No se encontraron hospitales con la especialidad: " << especialidad << endl;
        return;
    }

    // ordenamos reutilizando el quicskort del punto 4 ya que el criterio 1 era camas.
    int cantidadHospitalesFiltrados = hospitalesFiltrados.size();

    Hospital* vectorHeapFiltrados = new Hospital[cantidadHospitalesFiltrados];

    for (int i = 0; i < cantidadHospitalesFiltrados; i++)
    {
        vectorHeapFiltrados[i] = hospitalesFiltrados[i];
    }
    
    quickSort(vectorHeapFiltrados, 0, hospitalesFiltrados.size() - 1, 1);

    cout << "\n--- Hospitales con especialidad en " << especialidad << " ---" << endl;
    for (int i = 0; i < cantidadHospitalesFiltrados; i++)
    {
        Hospital h = vectorHeapFiltrados[i];
         cout << "Hospital: " << h.getCodigo() << " | Camas disponibles: " << h.getCapacidad() << " | Especialidades totales : " << h.getEspecialidades() << endl;
    }
    delete[] vectorHeapFiltrados;
}

/// *********** PARTE B ***************
//B.1
int SistemaHospitalario::calcularPacientesAtendidos(string codigoHospital, int fechaDesde, int fechaHasta) {
    int indice = obtenerIndice(codigoHospital);

    if (indice == -1) {
        cout << "Error: El hospital con codigo " << codigoHospital << " no existe." << endl;
        return 0;
    }
    
    vector<Turno> turnosHospital = this->listaHospitales[indice].getTurnos();
    int totalPacientes = 0;

    for (size_t i = 0; i < turnosHospital.size(); i++) {
        Turno t = turnosHospital[i];

        if (t.getFecha() >= fechaDesde && t.getFecha() <= fechaHasta) {
            totalPacientes++;
        }
    }

    return totalPacientes;
}

//B.2
//Busqueda Binaria
int buscarFinDeSemanaBinario(const vector<Turno>& turnos, int desdeIndice, int fechaLimite) {
    int inicio = desdeIndice;
    int fin = turnos.size() - 1;
    int resultado = turnos.size();

    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;

        if (turnos[medio].getFecha() > fechaLimite) {
            resultado = medio;
            fin = medio - 1;
        } else {
            inicio = medio + 1;
        }
    }
    return resultado;
}

void SistemaHospitalario::detectarSobrecargaDePacientes(int x) {
    cout << "--- REPORTES DE HOSPITALES CON SOBRECARGA ---" << endl;
    bool huboSobrecarga = false;

    for (size_t i = 0; i < this->listaHospitales.size(); i++) {
        Hospital h = this->listaHospitales[i];
        int cantidadTurnos = h.getTurnos().size(); 
        int capacidadCamas = h.getCapacidad(); 

        if (capacidadCamas == 0) {
            cout << "Camas no puede ser 0" << endl;
            return;
        }

        float porcentajeOcupacion = ((float)cantidadTurnos / capacidadCamas) * 100.0;
        bool superaPorFecha = false;
        
        vector<Turno> turnosHospital = h.getTurnos();

        SortUtils::quickSort(turnosHospital, [](const Turno &a, const Turno &b) {
            return a.getFecha() < b.getFecha();
        });

        for (size_t j = 0; j < turnosHospital.size(); j++) {
            int fechaInicio = turnosHospital[j].getFecha();
            int fechaLimite = fechaInicio + 6;

            int indiceLimite = buscarFinDeSemanaBinario(turnosHospital, j, fechaLimite);

            int ingresosEnSemana = indiceLimite - j;

            if (ingresosEnSemana > x) {
                superaPorFecha = true;
                break;
            }
        }

        if (porcentajeOcupacion >= 90 || superaPorFecha) {
            huboSobrecarga = true;
            cout << "El hospital " << h.getNombre() << " en " << h.getCiudad() << " esta SOBRECARGADO." << endl;
        }
    }

    if (!huboSobrecarga) {
        cout << "No se detectaron hospitales con SOBRECARGA. " << endl;
    }
}

//B.3
void SistemaHospitalario::buscarTurnosPorDNI(int dni) {
    int idBuscado = -1;

    for (size_t i = 0; i < this->listaPacientes.size(); i++) {
        if (this->listaPacientes[i].getDni() == dni) {
            idBuscado = this->listaPacientes[i].getIdPaciente();
            break; 
        }
    }

    if (idBuscado == -1) {
        cout << "No se encontro ningun paciente con el DNI: " << dni << endl;
        return;
    }

    cout << "--- TURNOS ASIGNADOS PARA EL PACIENTE (DNI: " << dni << ") ---" << endl;
    bool tieneTurnos = false;

    for (size_t i = 0; i < this->listaHospitales.size(); i++) {
        vector<Turno> turnosHospital = this->listaHospitales[i].getTurnos();

        for (size_t j = 0; j < turnosHospital.size(); j++) {
            Turno t = turnosHospital[j];

            if (t.getIdPaciente() == idBuscado) {
                tieneTurnos = true;
                cout << "Hospital: " << this->listaHospitales[i].getCodigo() << " | Fecha: " << t.getFecha() << " | Medico ID: " << t.getIdMedico() << endl;
            }
        }
    }

    if (!tieneTurnos) {
        cout << "El paciente no tiene turnos registrados en ningun hospital." << endl;
    }
}

//B.4
void SistemaHospitalario::mostrarEnOrden() {
    ColaPrioridad copiaCola = listaDeEspera;
    cout << "--- PACIENTES EN ESPERA (ORDEN DE PRIORIDAD) ---" <<endl;
    while (!copiaCola.esVacia()) {
        Paciente p = copiaCola.desencolar();
        cout << "Prioridad: " << p.getPrioridad() << " | ID: " << p.getIdPaciente() <<  " | Cod. Hospital: " << p.getCodHospital() <<  " | DNI: " << p.getDni() << " | Fecha: " << p.getFechaIngreso() << " | Diagnostico: " << p.getDiagnostico() << endl;
    }
}

void SistemaHospitalario::insertarPaciente(Paciente p) {
    listaDeEspera.encolar(p);
}

Paciente SistemaHospitalario::extraerMasPrioritario() {
    return listaDeEspera.desencolar();
}

void SistemaHospitalario::actualizarPrioridad(int id, int nuevaPrio) {
    listaDeEspera.actualizarPrioridad(id, nuevaPrio);
}

bool SistemaHospitalario::listaPrioridadVacia() {
    return listaDeEspera.esVacia();
}

//B.5
void SistemaHospitalario::listarTurnosCronologicamente(int idMedico) {
    vector<Turno> turnosDelMedico;

    //Revisamos los turnos del medico en los distintos hospitales
    for (size_t i = 0; i < this->listaHospitales.size(); i++) {
        vector<Turno> turnosHospital = this->listaHospitales[i].getTurnos();

        for (size_t j = 0; j < turnosHospital.size(); j++) {
            if (turnosHospital[j].getIdMedico() == idMedico) {
                turnosDelMedico.push_back(turnosHospital[j]);
            }
        }
    }

    //Que pasa si el medico no tiene turnos:
    if (turnosDelMedico.empty()) {
        cout << "No se encontraron turnos registrados para el Medico ID: " << idMedico << endl;
        return;
    }
    
    //Aplicamos Quicksort
    SortUtils::quickSort(turnosDelMedico, [](const Turno &izquierdo, const Turno &derecho) {
        return izquierdo.getFecha() < derecho.getFecha(); // Menor a mayor (cronológico)
    });

    //Listamos los turnos del Id ordenados cronologicamente
    cout << "TURNOS CRONOLOGICOS DEL MEDICO ID: " << idMedico << endl;
    for (size_t i = 0; i < turnosDelMedico.size(); i++) {
        Turno t = turnosDelMedico[i];
        cout << "- Fecha: " << t.getFecha() 
             << " | Especialidad: " << t.getEspecialidad()
             << " | Paciente ID: " << t.getIdPaciente() 
             << " | Duracion: " << t.getDuracionMin() << " min." << endl;
    }
}

// AGREGAR TURNO A HOSPITAL
void SistemaHospitalario::agregarTurnoAHospital(string codigoHospital, Turno nuevoTurno) {
    int indice = obtenerIndice(codigoHospital);

    if (indice != -1) {
        this->listaHospitales[indice].registrarTurno(nuevoTurno);
    } else {
        cout << "Error: El hospital con codigo " << codigoHospital << " no existe. No se pudo cargar el turno." << endl;
    }
}

// REGISTRAR NUEVO PACIENTE
void SistemaHospitalario::registrarPaciente(Paciente nuevoPaciente)
{
    listaPacientes.push_back(nuevoPaciente);

    Diagnostico* encontrado =
        arbolDiagnosticos.buscar(
            nuevoPaciente.getDiagnostico());

    if(encontrado == nullptr)
    {
        insertarDiagnostico(
            nuevoPaciente.getDiagnostico(),
            1);
    }
    else
    {
        incrementarFrecuenciaDiagnostico(
            nuevoPaciente.getDiagnostico());
    }

}


/// *********** PARTE C ***************

void SistemaHospitalario::insertarDiagnostico(string nombre, int frecuencia)
{
    Diagnostico* encontrado = arbolDiagnosticos.buscar(nombre);

    if(encontrado != nullptr)
    {
        cout << "El diagnostico ya existe." << endl;
        return;
    }

    Diagnostico* nuevo = new Diagnostico(nombre, frecuencia);
    Diagnostico* nuevoAVL = new Diagnostico(nombre, frecuencia);

    arbolDiagnosticos.insertar(nuevo);
    arbolAVLDiagnosticos.insertar(nuevoAVL);
}

void SistemaHospitalario::incrementarFrecuenciaDiagnostico(string nombre)
{
    arbolDiagnosticos.incrementarFrecuencia(nombre);
    arbolAVLDiagnosticos.incrementarFrecuencia(nombre);
}

void SistemaHospitalario::listarDiagnosticos()
{
    arbolDiagnosticos.listarDiagnosticos();
}

Diagnostico* SistemaHospitalario::mostrarDiagnosticoFrecuente()
{
    return arbolDiagnosticos.diagnosticoMasFrecuente();
}

void SistemaHospitalario::eliminarDiagnostico(string nombre)
{
    arbolDiagnosticos.eliminar(nombre);
    arbolAVLDiagnosticos.eliminar(nombre);
}

bool SistemaHospitalario::detectarDesbalanceo()
{
    return arbolDiagnosticos.estaDesbalanceado();
}

int SistemaHospitalario::alturaArbolDiagnosticos()
{
    return arbolDiagnosticos.altura();
}

void SistemaHospitalario::mostrarArbolDiagnosticos()
{
    arbolDiagnosticos.mostrarArbol();
}

int SistemaHospitalario::alturaArbolAVLDiagnosticos()
{
    return arbolAVLDiagnosticos.altura();
}

void SistemaHospitalario::listarDiagnosticosAVL()
{
    arbolAVLDiagnosticos.listarDiagnosticos();
}

void SistemaHospitalario::mostrarArbolAVLDiagnosticos()
{
    arbolAVLDiagnosticos.mostrarArbol();
}