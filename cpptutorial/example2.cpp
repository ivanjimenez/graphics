#include <iostream>
#include <chrono>

using namespace std;

void long_task() {
    const int filas = 100000000;
    const int columnas = 100000000;
    
    // Crear una matriz grande utilizando un arreglo dinámico
    int **matriz = new int*[filas];
    for (int i = 0; i < filas; ++i) {
        matriz[i] = new int[columnas];
    }
    
    // Inicializar la matriz con algún valor (por ejemplo, ceros)
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = 0;
        }
    }
}

int main() {

   // Capturar el tiempo de inicio
    auto start = std::chrono::high_resolution_clock::now();
    
    // Aquí va el código cuyo tiempo de ejecución deseas medir
    // Por ejemplo, una serie de instrucciones

    void long_task();
    
    // Capturar el tiempo de finalización
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calcular la diferencia de tiempo en segundos
    std::chrono::duration<double> elapsed = end - start;
    
    // Imprimir el tiempo transcurrido
    std::cout << "Tiempo transcurrido: " << elapsed.count() << " segundos" << std::endl;
    
}