#include "../header/Ambulancia.h"
#include <algorithm>

namespace
{
    constexpr float margenPeso = 0.0001f;

    /*
    // QuickSort propio para valor/peso. Deja comentado para ver si reemplaza a std::sort.

    bool esMayorRelacionValorPeso(const Insumo &primerInsumo, const Insumo &segundoInsumo)
    {
        float relacionPrimera = primerInsumo.getPesoKg() > 0.0f
            ? static_cast<float>(primerInsumo.getValorClinico()) / primerInsumo.getPesoKg()
            : static_cast<float>(primerInsumo.getValorClinico());

        float relacionSegunda = segundoInsumo.getPesoKg() > 0.0f
            ? static_cast<float>(segundoInsumo.getValorClinico()) / segundoInsumo.getPesoKg()
            : static_cast<float>(segundoInsumo.getValorClinico());

        if (relacionPrimera == relacionSegunda)
        {
            return primerInsumo.getValorClinico() > segundoInsumo.getValorClinico();
        }

        return relacionPrimera > relacionSegunda;
    }

    int particionInsumos(vector<Insumo> &insumos, int inicio, int fin)
    {
        Insumo pivote = insumos[fin];
        int indiceMenores = inicio - 1;

        for (int j = inicio; j < fin; j++)
        {
            if (esMayorRelacionValorPeso(insumos[j], pivote))
            {
                indiceMenores++;
                Insumo auxiliar = insumos[indiceMenores];
                insumos[indiceMenores] = insumos[j];
                insumos[j] = auxiliar;
            }
        }

        Insumo auxiliar = insumos[indiceMenores + 1];
        insumos[indiceMenores + 1] = insumos[fin];
        insumos[fin] = auxiliar;

        return indiceMenores + 1;
    }

    void quickSortInsumos(vector<Insumo> &insumos, int inicio, int fin)
    {
        if (inicio < fin)
        {
            int indicePivote = particionInsumos(insumos, inicio, fin);

            quickSortInsumos(insumos, inicio, indicePivote - 1);
            quickSortInsumos(insumos, indicePivote + 1, fin);
        }
    }
    */
}

// Inicializa el resultado de la optimización sin elementos seleccionados ni nodos explorados.
Ambulancia::ResultadoOptimizacion::ResultadoOptimizacion()
{
    this->valorTotal = 0;
    this->pesoTotal = 0.0f;
    this->nodosExplorados = 0;
}

// Crea una ambulancia vacía con identificador y capacidad por defecto.
Ambulancia::Ambulancia()
{
    this->idAmbulancia = 0;
    this->capacidad = 0.0f;
}

// Crea una ambulancia con identificador y capacidad definidos por el usuario.
Ambulancia::Ambulancia(int idAmbulancia, float capacidad)
{
    this->idAmbulancia = idAmbulancia;
    this->capacidad = capacidad;
}

// Compara dos insumos por la relación valor clínico / peso para priorizar los más convenientes.
bool Ambulancia::compararPorRelacionValorPeso(const Insumo &primerInsumo, const Insumo &segundoInsumo)
{
    float relacionPrimera = primerInsumo.getPesoKg() > 0.0f ? static_cast<float>(primerInsumo.getValorClinico()) / primerInsumo.getPesoKg() : static_cast<float>(primerInsumo.getValorClinico());
    float relacionSegunda = segundoInsumo.getPesoKg() > 0.0f ? static_cast<float>(segundoInsumo.getValorClinico()) / segundoInsumo.getPesoKg() : static_cast<float>(segundoInsumo.getValorClinico());

    if (relacionPrimera == relacionSegunda)
    {
        return primerInsumo.getValorClinico() > segundoInsumo.getValorClinico();
    }

    return relacionPrimera > relacionSegunda;
}

// Actualiza la mejor solución encontrada si la selección actual tiene mayor valor o mismo valor con menor peso.
void Ambulancia::actualizarMejorCarga(const vector<Insumo> &seleccionActual, float pesoActual, int valorActual, ResultadoOptimizacion &mejorResultado) const
{
    if (valorActual > mejorResultado.valorTotal || (valorActual == mejorResultado.valorTotal && pesoActual < mejorResultado.pesoTotal))
    {
        mejorResultado.insumosSeleccionados = seleccionActual;
        mejorResultado.valorTotal = valorActual;
        mejorResultado.pesoTotal = pesoActual;
    }
}

// Explora todas las combinaciones posibles sin poda para resolver la mochila por backtracking puro.
void Ambulancia::backtrackingPuroRec(const vector<Insumo> &listaInsumos, size_t indice, float pesoActual, int valorActual, vector<Insumo> &seleccionActual, ResultadoOptimizacion &mejorResultado, long long &nodosExplorados) const
{
    nodosExplorados++;

    if (indice == listaInsumos.size())
    {
        actualizarMejorCarga(seleccionActual, pesoActual, valorActual, mejorResultado);
        return;
    }

    actualizarMejorCarga(seleccionActual, pesoActual, valorActual, mejorResultado);

    if (pesoActual + listaInsumos[indice].getPesoKg() <= this->capacidad + margenPeso)
    {
        seleccionActual.push_back(listaInsumos[indice]);
        backtrackingPuroRec(listaInsumos, indice + 1, pesoActual + listaInsumos[indice].getPesoKg(), valorActual + listaInsumos[indice].getValorClinico(), seleccionActual, mejorResultado, nodosExplorados);
        seleccionActual.pop_back();
    }

    backtrackingPuroRec(listaInsumos, indice + 1, pesoActual, valorActual, seleccionActual, mejorResultado, nodosExplorados);
}

// Calcula una cota optimista de valor usando una relajación fraccionaria para decidir si conviene seguir explorando.
double Ambulancia::calcularCotaSuperior(const vector<Insumo> &listaInsumosOrdenada, size_t indice, float pesoActual, int valorActual) const
{
    double cota = static_cast<double>(valorActual);
    float pesoRestante = this->capacidad - pesoActual;

    for (size_t i = indice; i < listaInsumosOrdenada.size() && pesoRestante > 0.0f; i++)
    {
        const Insumo &insumo = listaInsumosOrdenada[i];

        if (insumo.getPesoKg() <= margenPeso)
        {
            cota += static_cast<double>(insumo.getValorClinico());
        }
        else if (insumo.getPesoKg() <= pesoRestante)
        {
            cota += static_cast<double>(insumo.getValorClinico());
            pesoRestante -= insumo.getPesoKg();
        }
        else
        {
            cota += static_cast<double>(insumo.getValorClinico()) * (static_cast<double>(pesoRestante) / insumo.getPesoKg());
            break;
        }
    }

    return cota;
}

// Explora la mochila con branch and bound, descartando ramas que no pueden superar la mejor solución conocida.
void Ambulancia::branchAndBoundRec(const vector<Insumo> &listaInsumosOrdenada, size_t indice, float pesoActual, int valorActual, vector<Insumo> &seleccionActual, ResultadoOptimizacion &mejorResultado, long long &nodosExplorados) const
{
    nodosExplorados++;

    actualizarMejorCarga(seleccionActual, pesoActual, valorActual, mejorResultado);

    if (indice == listaInsumosOrdenada.size())
    {
        return;
    }

    if (calcularCotaSuperior(listaInsumosOrdenada, indice, pesoActual, valorActual) <= static_cast<double>(mejorResultado.valorTotal))
    {
        return;
    }

    const Insumo &insumoActual = listaInsumosOrdenada[indice];

    if (pesoActual + insumoActual.getPesoKg() <= this->capacidad + margenPeso)
    {
        seleccionActual.push_back(insumoActual);
        branchAndBoundRec(listaInsumosOrdenada, indice + 1, pesoActual + insumoActual.getPesoKg(), valorActual + insumoActual.getValorClinico(), seleccionActual, mejorResultado, nodosExplorados);
        seleccionActual.pop_back();
    }

    branchAndBoundRec(listaInsumosOrdenada, indice + 1, pesoActual, valorActual, seleccionActual, mejorResultado, nodosExplorados);
}

// Getters
// Devuelve el identificador único de la ambulancia.
int Ambulancia::getIdAmbulancia() const
{
    return this->idAmbulancia;
}

// Devuelve la capacidad máxima de carga de la ambulancia.
float Ambulancia::getCapacidad() const
{
    return this->capacidad;
}

// Calcula el peso total actualmente cargado en la ambulancia.
float Ambulancia::getPesoCargado() const
{
    float pesoTotal = 0.0f;

    for (size_t i = 0; i < this->cargaActual.size(); i++)
    {
        pesoTotal += this->cargaActual[i].getPesoKg();
    }

    return pesoTotal;
}

// Retorna la lista de insumos cargados actualmente.
const vector<Insumo> &Ambulancia::getCarga() const
{
    return this->cargaActual;
}

// Indica si todavía queda capacidad disponible para sumar insumos.
bool Ambulancia::quedaLugar() const
{
    return this->getPesoCargado() + margenPeso < this->capacidad;
}





// Agrega un insumo a la carga solo si no supera el límite de peso permitido.
void Ambulancia::agregarInsumo(Insumo unInsumo)
{
    if (this->getPesoCargado() + unInsumo.getPesoKg() <= this->capacidad + margenPeso)
    {
        this->cargaActual.push_back(unInsumo);
    }
}

// Ejecuta el algoritmo de backtracking puro y devuelve la mejor combinación hallada.
Ambulancia::ResultadoOptimizacion Ambulancia::resolverBacktrackingPuro(const vector<Insumo> &listaInsumos) const
{
    ResultadoOptimizacion mejorResultado;
    vector<Insumo> seleccionActual;
    long long nodosExplorados = 0;

    backtrackingPuroRec(listaInsumos, 0, 0.0f, 0, seleccionActual, mejorResultado, nodosExplorados);
    mejorResultado.nodosExplorados = nodosExplorados;

    return mejorResultado;
}

// Ejecuta branch and bound ordenando primero los insumos por conveniencia valor/peso.
Ambulancia::ResultadoOptimizacion Ambulancia::resolverBranchAndBound(const vector<Insumo> &listaInsumos) const
{
    vector<Insumo> listaOrdenada = listaInsumos;
    // Reemplazar std::sort por quickSortInsumos?.
    sort(listaOrdenada.begin(), listaOrdenada.end(), compararPorRelacionValorPeso);
    // quickSortInsumos(listaOrdenada, 0, static_cast<int>(listaOrdenada.size()) - 1);

    ResultadoOptimizacion mejorResultado;
    vector<Insumo> seleccionActual;
    long long nodosExplorados = 0;

    branchAndBoundRec(listaOrdenada, 0, 0.0f, 0, seleccionActual, mejorResultado, nodosExplorados);
    mejorResultado.nodosExplorados = nodosExplorados;

    return mejorResultado;
}

/*
Justificacion (por IA) del uso de memoria dinamica en Ambulancia e Insumo:

La clase Ambulancia administra colecciones cuyo tamano no es fijo en tiempo de compilacion, por lo que su modelado
resulta naturalmente asociado a memoria dinamica. En particular, la carga actual de la ambulancia, la lista de insumos
seleccionados y las colecciones temporales utilizadas por los algoritmos de backtracking se representan mediante
std::vector, una estructura que reserva almacenamiento en heap para crecer o reducirse segun las necesidades del
algoritmo.

En el caso de Insumo, la clase se mantiene como una entidad de valor, simple y liviana, compuesta por atributos basicos
como identificador, nombre, peso y valor clinico. No requiere administrar memoria manualmente, ya que su funcion es
representar informacion elemental que luego es almacenada dentro de estructuras dinamicas de mayor nivel.

Desde el punto de vista del diseno, la utilizacion de memoria dinamica se justifica por la cantidad variable de insumos
que debe gestionar una ambulancia y por la necesidad de conservar soluciones parciales y optimas durante la exploracion
del espacio de busqueda. En consecuencia, el heap aparece como soporte de las colecciones dinamicas, mientras que
Insumo permanece como tipo de dato por valor.
*/