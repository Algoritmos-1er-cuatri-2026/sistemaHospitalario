# Sistema De Gestión Hospitalaria - Módulo D

## Descripción General
Este documento describe el módulo de **Ambulancias e Insumos**, desarrollado en C++17 como parte del Trabajo Práctico de la materia **Algoritmos**. El objetivo del módulo es modelar una ambulancia con capacidad limitada y seleccionar la mejor combinación de insumos médicos para maximizar el valor clínico total sin superar el peso disponible.

El módulo permite resolver el problema por dos enfoques distintos:
- **Backtracking puro**, que explora todas las combinaciones posibles.
- **Branch and Bound**, que aplica poda para reducir el espacio de búsqueda.

Además, el sistema incorpora persistencia simple en archivo de texto para trabajar con una lista de insumos reutilizable desde el menú.

## Requisitos
- **Compilador:** GCC con soporte para C++17 o superior.
- **Sistema operativo:** Windows recomendado, porque el programa usa `system("pause")` para volver al menú.
- **Archivos de datos:** carpeta `datos/` con el archivo `insumos.txt`.

## Compilación y Ejecución

### Compilación manual
Desde la raíz del proyecto:
```bash
g++ -std=c++17 -Wall -Wextra main.cpp cpp/*.cpp -Iheader -o main.exe
```

### Compilación con script
En Windows también se puede usar:
```bash
build.bat
```

### Ejecución
Una vez compilado:
```bash
./main.exe
```

## Estructura Relacionada Al Módulo
- **`header/Ambulancia.h`**: interfaz de la clase `Ambulancia`.
- **`cpp/Ambulancia.cpp`**: implementación de la optimización de carga.
- **`header/Insumo.h`**: interfaz de la clase `Insumo`.
- **`cpp/Insumo.cpp`**: implementación de lectura y guardado de insumos.
- **`datos/insumos.txt`**: archivo de texto con los insumos disponibles.

## Clases Implementadas

### Insumo
Representa un insumo médico con:
- nombre
- peso en kg
- valor clínico

También incluye métodos estáticos para:
- leer insumos desde archivo
- guardar la lista de insumos en archivo

### Ambulancia
Representa una ambulancia con:
- id
- capacidad máxima
- carga actual

La clase implementa:
- optimización por backtracking puro
- optimización por branch and bound
- cálculo del peso cargado
- verificación de espacio disponible
- almacenamiento de la mejor carga encontrada

## Funcionalidades Implementadas

### 1. Cargar y listar insumos
El menú permite leer los insumos desde `datos/insumos.txt`, mostrarlos por pantalla y agregar nuevos insumos al archivo.

### 2. Crear una ambulancia
Se puede ingresar un id y una capacidad para crear una ambulancia vacía. El sistema muestra:
- id de la ambulancia
- capacidad total
- peso cargado actual
- si todavía queda lugar disponible

### 3. Resolver por Backtracking Puro
Este método analiza todas las combinaciones posibles de insumos y devuelve la mejor selección que no supera la capacidad.

Complejidad:
- Mejor caso: $\Theta(2^n)$, porque igual debe revisar el espacio completo de decisiones.
- Peor caso: $\Theta(2^n)$, ya que recorre todo el árbol binario de inclusión/exclusión.

Cantidad de nodos recorridos:
- Recorre todos los nodos del árbol de decisiones: $2^{n+1} - 1$.
- Para $n = 3$, el recorrido completo tiene $2^{4} - 1 = 15$ nodos.

Ejemplo corto con 3 insumos:
```txt
Capacidad de la ambulancia: 5.0 kg
Insumos disponibles:
1. gasas   | peso: 2.0 | valor: 4
2. vendas  | peso: 3.0 | valor: 5
3. suero   | peso: 4.0 | valor: 7
```

Resultado posible por backtracking puro:
```txt
Seleccion: gasas + vendas
Peso total: 5.0 kg
Valor total: 9
```

### 4. Resolver por Branch and Bound
Este método ordena los insumos por relación valor/peso y aplica poda para descartar ramas que no pueden superar la mejor solución encontrada.

Nota importante:
- Branch and Bound necesita trabajar sobre el vector de insumos ordenado por relación valor/peso.
- Esto se hace porque la cota superior se calcula tomando primero los insumos más convenientes; así la estimación optimista es más fuerte y la poda funciona mejor.
- Si el vector no está ordenado, la cota puede ser menos informativa y el algoritmo termina explorando más ramas de las necesarias.
- El ordenamiento no cambia la solución óptima final, pero sí mejora la eficiencia del recorrido.

Complejidad:
- Mejor caso: cercana a $\Theta(n)$ para la exploración, más el costo de ordenar los insumos, porque la poda elimina gran parte del árbol.
- Peor caso: $\Theta(2^n)$, si la poda no logra descartar suficientes ramas.

Cantidad de nodos recorridos:
- Es variable y depende de cuántas ramas puedan podarse.
- En el mejor caso recorre muchos menos nodos que el backtracking puro.
- En el peor caso puede llegar al mismo orden que el árbol completo: $2^{n+1} - 1$.
- Para $n = 3$, el máximo teórico también es 15 nodos, pero normalmente Branch and Bound recorre menos.

Ejemplo corto con los mismos 3 insumos:
```txt
Capacidad de la ambulancia: 5.0 kg
Insumos ordenados por relacion valor/peso:
1. gasas   | 4/2 = 2.0
2. suero   | 7/4 = 1.75
3. vendas  | 5/3 = 1.66
```

Resultado posible por branch and bound:
```txt
Seleccion: gasas + vendas
Peso total: 5.0 kg
Valor total: 9
```

### Nota Sobre El QuickSort Implementado
El ordenamiento interno del módulo se resuelve con un QuickSort propio sobre el vector de insumos.

Funcionamiento general:
- Se elige como pivote el último insumo del tramo actual.
- Se recorren los elementos y se colocan a la izquierda los que tienen mayor relación valor/peso que el pivote.
- Al finalizar la partición, el pivote queda en su posición definitiva.
- Luego se repite el proceso recursivamente sobre la parte izquierda y la parte derecha.

Criterio de orden:
- Primero se compara la relación valor clínico / peso.
- Si dos insumos tienen la misma relación, se desempata por valor clínico total.

Idea del algoritmo:
- Es un ordenamiento in-place, porque reorganiza el mismo vector sin usar una estructura auxiliar grande.
- Su mejor caso es $\Theta(n \log n)$ y su peor caso es $\Theta(n^2)$, dependiendo de cómo queden los pivotes.
- En este proyecto se usa para preparar los insumos antes de aplicar Branch and Bound.

### 5. Comparar nodos explorados
Ambos enfoques devuelven la cantidad de nodos explorados, lo que permite comparar el costo de exploración entre la versión exhaustiva y la versión con poda.

## Menú Del Sistema
La opción correspondiente en el menú principal es:

`4 - Gestion de ambulancias e insumos`

Dentro de ese submenú se encuentran las siguientes opciones:
- `1 - Registrar nuevo insumo`
- `2 - Listar insumos`
- `3 - Crear ambulancia vacia`
- `4 - Resolver por backtracking puro`
- `5 - Resolver por branch and bound`

## Formato Del Archivo De Insumos
Cada línea de `datos/insumos.txt` debe seguir este formato:

```txt
nombre pesoKg valorClinico
```

Ejemplo:

```txt
gasas 0.2 5
vendas 0.3 8
suero 1.0 10
```

## Ejemplo De Uso

### Agregar un insumo
1. Seleccionar `4 - Gestion de ambulancias e insumos`.
2. Seleccionar `1 - Registrar nuevo insumo`.
3. Ingresar el nombre, peso y valor clínico.

### Listar insumos
1. Seleccionar `4 - Gestion de ambulancias e insumos`.
2. Seleccionar `2 - Listar insumos`.

### Crear una ambulancia
1. Seleccionar `4 - Gestion de ambulancias e insumos`.
2. Seleccionar `3 - Crear ambulancia vacia`.
3. Ingresar el id y la capacidad.

### Resolver por backtracking
1. Seleccionar `4 - Gestion de ambulancias e insumos`.
2. Seleccionar `4 - Resolver por backtracking puro`.
3. Ingresar el id y la capacidad.

### Resolver por branch and bound
1. Seleccionar `4 - Gestion de ambulancias e insumos`.
2. Seleccionar `5 - Resolver por branch and bound`.
3. Ingresar el id y la capacidad.

## Observaciones Técnicas
- La solución trabaja con una comparación de peso usando un margen pequeño para evitar problemas de precisión con números flotantes.
- Branch and Bound usa una ordenación propia de los insumos por relación valor/peso.
- La persistencia es simple y está basada en archivos de texto, por lo que no requiere base de datos externa.

## Objetivo Académico
Este módulo permite comparar dos estrategias clásicas de búsqueda combinatoria y mostrar por qué una poda bien aplicada reduce el espacio de exploración respecto del backtracking puro. También deja visible la integración entre estructura de datos, persistencia básica y menú de consola.