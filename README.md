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
- **`main.cpp`**: Punto de entrada principal de la aplicación.
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