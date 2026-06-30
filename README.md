# Sistema De Gestión Hospitalaria

## Descripción General
Este sistema es un Trabajo Práctico desarrollado para la materia **Algoritmos**. Consiste en una aplicación de consola en C++ diseñada para administrar de manera eficiente redes hospitalarias, asignación de turnos médicos, flujos de pacientes mediante prioridades y la clasificación de diagnósticos clínicos.
## Requisitos
- **Compilador:** GCC con soporte para C++17 o superior (MinGW en Windows / GCC en Linux/Mac).
- **Consola:** PowerShell, CMD o terminal Bash con acceso a las variables de entorno de `g++`.
- **Archivos de Entrada:** Datos persistidos en formato de texto plano (`.txt`) dentro de la carpeta correspondiente.
## Compilación y Ejecución
### Opción 1: Compilación Manual por Consola
Desde la raíz del proyecto en Bash:
```bash
g++ -std=c++17 -Wall -Wextra main.cpp cpp/*.cpp -o main.exe
```
### Opción 2: Compilación mediante Script (build.bat)
Si estás en Windows, podés ejecutar directamente:
```bash
build.bat
```
### Ejecución
Una vez compilado de forma exitosa, el sistema genera el ejecutable main.exe. Correr mediante:
```bash
./main.exe
```
## Estructura Del Proyecto
La arquitectura del código fuente está organizada de la siguiente manera:
- **`main.cpp`**: Punto de entrada principal de la aplicación, encargado de la lectura de todos los archivos .txt.
- **`cpp/`**: Carpeta que contiene todos los archivos de implementación fuente (`.cpp`).
- **`header/`**: Carpeta que almacena las cabeceras y definiciones de clases (`.h`).
- **`datos/`**: Carpeta donde se alojan los archivos de texto del sistema (ej: `hospital.txt`, `turnos.txt`).
## Módulos Implementados

### Punto A - Gestión De Hospitales

### Punto B - Gestión De Pacientes Y Turnos

### Punto C - Árbol De Diagnósticos

### Punto D - Optimización De Insumos

## Funcionalidades

### Punto A - Gestión de Hospitales
Mostrar la información completa de un hospital dado su código. 
- Agregar un nuevo hospital al sistema. 
- Eliminar un hospital existente (y reasignar sus pacientes activos al hospital más cercano 
disponible). 
- Listar todos los hospitales ordenados por: capacidad de camas, cantidad de personal 
médico o presupuesto anual. 
- Dado un hospital de origen y uno de destino, calcular la ruta de derivación de menor 
tiempo para trasladar un paciente crítico (implementar Dijkstra). 
- Buscar hospitales que ofrezcan una especialidad específica y ordenarlos por 
disponibilidad de camas. 
### Punto B - Árbol De Diagnósticos
- Calcular el total de pacientes atendidos por rango de fechas.
- Detectar hospitales con sobrecarga por ocupación o picos de ingresos semanales.
- Buscar de forma eficiente todos los turnos de un paciente mediante su DNI.
- Administrar la lista de espera de la guardia utilizando una cola de prioridad (Min-Heap).
- Listar los turnos de un médico ordenados cronológicamente mediante QuickSort genérico.

### Punto C - Árbol De Diagnósticos

El sistema mantiene un árbol binario de búsqueda de diagnósticos ordenado por frecuencia de aparición. En caso de empate de frecuencia, se utiliza el nombre del diagnóstico como criterio secundario para mantener un orden total.

También se implementa una versión AVL para comparar la altura resultante contra el BST simple.

Funcionalidades implementadas:

- Insertar diagnóstico con frecuencia inicial.
- Incrementar frecuencia de un diagnóstico existente.
- Listar diagnósticos mediante recorrido inorder.
- Encontrar el diagnóstico más frecuente.
- Eliminar diagnóstico manteniendo la propiedad BST.
- Calcular altura del árbol.
- Detectar desbalance.
- Comparar altura entre BST y AVL.

### Punto D - Optimización de Insumos con Backtracking 
- Optimización de Carga Insumos (Backtracking Puro):** Seleccionar el subconjunto de insumos médicos que maximice el valor clínico total sin superar el límite de peso de la ambulancia mediante exploración exhaustiva.
- Optimización Eficiente (Branch & Bound):** Optimizar la carga aplicando podas al árbol de decisión para descartar ramas innecesarias cuando el valor potencial no supere al mejor ya encontrado.
- Comparar la cantidad de nodos explorados entre la versión con poda y sin poda utilizando distintos tamaños de entrada ($n = 10, 20, 30$).
- Determinar el costo computacional de ambos enfoques y evaluar la viabilidad de la Programación Dinámica como alternativa eficiente.

## Ejemplo de Uso

Desde la raíz del proyecto:

### Ejemplo de uso para Punto A:

1. Seleccionar desde el menu principal `1 - Gestion de Hospitales`.

### Consideraciones

> Se trabajó sobre los hospitales y las derivaciones como vectores dentro del archivo sistemaHospitalario.

> Hash: 

> Se decidió implementar a nuestro proyecto con direccionamiento abierto ya que los datos sobre los que se van a trabajar ya se encuentran almacenados en una estructura de este estilo, en el vector Hospital. 

> Se implementó linear probing como técnica para resolver colisiones en la tabla hash.

> El tamaño de la tabla hash se calcula en base a la cantidad de elementos en el vector Hospitales. Se realiza la división entre esa cantidad y 0.8, de esa manera se obtiene el número primo más cercano para crear la tabla.

> La función de hash utilizada es un cálculo que suma el valor de cada carácter del código de los hospitales según su valor ascii, y realiza el módulo con el tamaño de la tabla.

> La función inicializarTablaHash() arma la tabla, aplica la función hash recorriendo la lista de elementos del vector, y los almacena en un nuevo vector en las posiciones dadas, almacena el código del hospital y el índice dentro del vector original Hospitales.

>Se llama a inicializarTablaHash() inmediatamente después de la lectura de archivos en el main.


### Ejemplo de uso para Punto A.1:

1. Seleccionar `1 - Mostrar informacion de un hospital dado su codigo`.
2. Ingresar `HGA` -> Esto retornara la información del HospitalGarrahan

>    En un principio este ejercicio se resolvió iterando sobre el vector listaHospitales, recorriendo todos los elementos hasta encontrar el buscado, utilizando un algoritmo de complejidad lineal O(n)

>    Tras realizar modificaciones al código e incorporar la tabla de hash, se resolvió aplicando al código ingresado por el usuario la función hash, y si devuelve un número válido, entonces esa es el índice del hospital que buscamos, y podemos llamar a su método mostrarInformacion()

>    De esa manera la función no debe recorrer todos los elementos, por lo que su complejidad pasa a ser constante O(1).

### Ejemplo de uso para Punto A.2:

1. Seleccionar `2 - Agregar un nuevo hospital al sistema`.
2. Ingresar la información solicitada por consola ya que son datos obligatorios para la creacion de un hospital.

>    Un vez recibida la información, se realiza un push al vector de Hospitales agregando el nuevo hospital.
>	Se realizó una llamada a la función inicializarTablaHash() luego de agregar un nuevo hospital al vector hospitales para que siempre se mantenga un 20% de la tabla hash vacía.
3. Se recomienda volver a usar el punto A.1 con el nuevo código ingresado para validar su funcionamiento.

### Ejemplo de uso para Punto A.3:
1. Seleccionar `3 - Eliminar un hospital del sistema`.
2. Ingresar el código del hospital que se desee eliminar.
3. Se listaran los pacientes del sistema antes y despues de la eliminación para validar la derivación hacia el hospital más cercano.

>    Hash: Se realizó una llamada a la función inicializarTablaHash() luego de eliminar un hospital, ya que para la creación de la tabla de hash utilizamos ENUM que permite definir tipos de datos, en nuestras ubicaciones de la tabla hash, incorporates el dato estado, que puede ser Ocupado, o Libre.

>    Como no utilizamos un estado “Borrado”, no podemos marcar en donde teníamos un hospital tras su eliminación, lo que rompería el linear probing ya que el programa daría con un espacio “Libre”. Para evitar esta situación, la estrategia es inicializar la tabla hash cada vez que se elimina un hospital, de esa manera nos aseguramos que cada vez que se modifique la cantidad de elementos en el vector Hospitales la tabla vuelva a crearse en base a la cantidad real.


>    Se reutiliza el Dijkstra del punto A.5 para calcular el hospital más cercano, realizando la creación del grafo con construirGrafoMatriz() y ejecutamos el Dijsktra con ejecutarDijkstra() recorriendo la totalidad del grafo.

>    Al finalizar el Dijkstra recorremos todo el vector distancia modificando las variables menorTiempo e indiceMasCercano cada vez que encontremos una distancia menor a la actual( inicializamos en 9999). Al finalizar, utilizamos ese índice para encontrar el hospital más cercano.

>    Se decidió imprimir la lista de pacientes antes y después de eliminar un hospital, para poder demostrar por consola las derivaciones realizadas.

### Ejemplo de uso para Punto A.4:
1. Seleccionar `4. Listar hospitales ordenados (camas, personal o presupuesto)`.
2. Ingresar `1 para odernar por camas, 2 por personal medico o 3 por presupuesto anual`.

>    Para la resolución de este ejercicio se realizó la implementación del algoritmo de ordenamiento Quicksort ya que es de los algoritmos más rápidos, y a diferencia de mergesort, no necesita crear subarreglos, lo que se traduce en un mejor uso de la memoria del sistema.

>    Trabajamos sobre un nuevo arreglo de Hospitales inicializado en la memoria dinámica mediante punteros, el cual es una copia del vector Hospitales original. 

>    Ejecutamos quicksort utilizando el arreglo dinámico para optimizar memoria y retornamos los datos por pantalla imprimiendo en orden los elementos del arreglo dinámico. Una vez finalizado, liberamos la memoria con delete [ ]
    
>    Nuestro quicksort elige como pivote al último elemento del vectorHeap, y busca según el filtro elegido a los elementos menores al pivote para posicionarlos al comienzo del arreglo.

### Ejemplo de uso para Punto A.5:
1. Seleccionar `5. Calcular lista mas rapida entre dos hospitales`.
2. Ingresar los códigos del hospital origen y el hospital destino.

>   La estrategia utilizada fue convertir los códigos de los hospitales en índices numéricos para poder recorrerlos. 

>   Utilizamos cuatro funciones:
>  agregarDerivacion() : Realiza la carga en el vector listaDerivaciones en base a la información leída en el main sobre derivaciones.txt
>  construirGrafoMatriz() : Se crea una matriz cuadrada del tamaño de la cantidad de hospitales, lo que representa el grafo, y sus aristas se inicializan en 99999 para representar el infinito. Los elementos en la diagonal principal son 0.

>    Luego comienza a recorrer listaDerivaciones, utilizando una función que convierte los códigos en índices numéricos se reemplazan posiciones simétricas en la matriz, ya que estamos representando un grafo no dirigido.

>    ejecutarDijkstra() : Una vez que el grafo está armado, implementamos el Dijkstra inicializando tres nuevos vectores del tamaño de la cantidad total de hospitales:

>    Distancia: Un vector numérico inicializado en infinito, se actualiza almacenando los tiempos descubiertos.

>    Visitado: Un arreglo booleano inicializado en la memoria dinámica, con todas sus posiciones en falso, se actualiza a medida que se encuentra un hospital.

>    Padre: Un vector numérico inicializado en -1, se actualiza en cada posición para recordar a través de qué elemento llegamos al actual.

>    Se inicializa con 0 la pos del hospital origen dentro del vector Distancia para que el algoritmo sepa dónde comenzar.

>    Recorre buscando el hospital más cercano no visitado, una vez encontrado lo marca como visitado y suma el tiempo entre el hospital actual + viaje hacia el vecino, si es menor que la que guardamos en esa misma pos en el vector Distancia, la reemplaza, y guarda en esa pos del vector Padre el índice del hospital actual, para saber a través de cual llegamos a ese vecino.

>    Al finalizar, se elimina el arreglo Visitado que se encontraba en la memoria dinámica con delete [ ].

>    calcularRutaMasRapida() : Ejecuta las funciones anteriores tomando como valor inicial un código origen y retornando la distancia hacia un código destino.

>    Se incorporaron tiempos de derivación al archivo derivaciones.txt entre nuevos hospitales para poder testear la función.

>    Se probó con el caso HGA (Garrahan) hacia HAU ( Austral) : 

>    Opción directa : Tarda 120 minutos
>    Opción con vecinos : Tarda 30m hacia HCL, luego desde HCL tarda 60 a HAU, dando un total de 90 minutos.

### Ejemplo de uso para Punto A.6:
1. Seleccionar `6. Buscar hospitales por especialidad ordenados por capacidad de camas.`.
2. Ingresar la especialidad deseada.

>    Como estrategia inicial creamos una función en los hospitales, tieneEspecialidad(), que se encarga de validar si el hospital tiene la especialidad que le pasamos por parámetro. Como las especialidades en el archivo de hospitales.txt vienen todas juntas (Ej; Cardiología,Clínica,Cirugía) utilizamos el método .find que se encarga de comparar si el texto recibido forma parte parcial de la cadena, de esa manera ingresando solo una especialidad puede encontrarla.

>    Implementamos una función que convierte las especialidades del hospital, y el dato ingresado por el usuario en minúsculas, de esa manera la solución funciona sin importar si en el texto, o en la entrada del usuario, aparecen las especialidades con mayúsculas o minúsculas. Esta función se realizó sumándole 32 a cada carácter de la cadena, ya que es la diferencia en código ascii entre mayúsculas y minúsculas.

>    Creamos un nuevo vector de Hospitales en donde almacenamos únicamente aquellos que tienen la especialidad buscada, y reutilizamos el quicksort del ejercicio A.4, es por eso que también en este ejercicio manejamos la memoria dinámica, ya que el quicksort espera recibir un puntero a un arreglo dinámico, entonces instanciamos un nuevo array dinamico, y le copiamos la información real del vector de hospitales filtrados, de esa manera podemos reordenar este arreglo dinámico según capacidad de camas, que es un filtro que ya teníamos en el ejercicio A.4, y liberar la memoria al finalizar con delete [ ].

### Ejemplo de uso para Punto B:

1. Seleccionar desde el menu principal `2 - Gestion de Pacientes y Turnos`.

#### Ejemplo de uso para Punto B.1

2. Seleccionar `1 - Total pacientes atendidos por hospital/fecha`.
2. Ingresamos `HGA`.
3. Ingrese fecha de inicio (AAAAMMDD): `20260601`
4. Ingrese fecha de fin (AAAAMMDD): `20260607`

#### Ejemplo de uso para Punto B.2

1. Seleccionar `2 - Gestion de Pacientes y Turnos`.
2. Seleccionar `2 - Detectar hospitales con sobrecarga`.
3. Ingrese la cantidad maxima de ingresos semanales permitidos: `3`
4. Probar devuelta con: `5`

#### Ejemplo de uso para Punto B.3

1. Seleccionar `3 - Buscar turnos de un paciente (DNI)`.
2. Ingrese el DNI del paciente: `45000111`

#### Ejemplo de uso para Punto B.4

1. Seleccionar `4 - Gestionar lista de espera (Min-Heap)`.
2. Seleccionar `4 - Mostrar Cola de Prioridad`.
3. Devuelta en el Menu seleccionamos `3 - Actualizar Prioridad de Paciente segun ID`.
4. Ingresamos el ID del paciente: `4`
5. Ingresamos como nueva prioridad: `4`
6. Devuelta en el Menu seleccionamos `2 - Extraer Paciente mas Prioritario de Cola de Prioridad`.
7. Devuelta en el Menu seleccionamos `1 - Insertar Paciente a Cola de Prioridad`.
8. Ingresamos como Hospital: `HGA`, ID: `10`, DNI: `40555666`, Fecha: `20260630`, Diagnostico: `Fractura`, Prioridad: `1` y Peso: `60`

#### Ejemplo de uso para Punto B.5

1. Seleccionar `5 - Listar turnos de medico en orden cronologico`.
2. Ingrese el DNI del paciente: `2001`

### Ejemplo de uso para Punto C:

Desde el menú principal:

1. Seleccionar `3 - Arbol de Diagnosticos`.
2. Seleccionar `1 - Insertar diagnostico`.
3. Ingresar nombre y frecuencia inicial.
4. Seleccionar `2 - Incrementar frecuencia`.
5. Seleccionar `3 - Listar diagnosticos`.
6. Seleccionar `10 - Comparar alturas BST y AVL`.
Y algo de memoria dinámica:

Los diagnósticos se crean dinámicamente con `new`. Para evitar fugas de memoria, ambos árboles implementan destructores recursivos que liberan los nodos restantes al finalizar la vida útil de la estructura. Además, al eliminar un diagnóstico se libera explícitamente el nodo correspondiente con `delete`.