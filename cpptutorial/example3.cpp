#include <iostream>
#include <chrono>
using namespace std;

struct Person {
    unsigned int id;
    string Name;
    string Surname;
};


int main() {

    chrono::steady_clock::time_point begin;
    begin = chrono::steady_clock::now();

    // 1000 millones de iteraciones
    for (int i{0}; i < 2000000000; i++);

    // timestamp de final
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // Imprimir el tiempo transcurrido
    std::cout << "Tiempo: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000<< "s" << std::endl;

    return 0;    
}