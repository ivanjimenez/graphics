#include <iostream>
#include <string>
#include <Windows.h>
#include <deque>
#include <algorithm>
#include <clocale>

using namespace std;

void ImprimeCola(deque<int> q){
    for (int item : q){
        cout << " " << item;
    }
    cout<<endl;
}

const double PI {3.14159};

class Cilindro {
    public:
        double volumen() {
            return PI * radio * radio * altura; 
        }
    
    public:
        double radio{1};
        double altura{1};
};

int main() {
    Cilindro cilindro1;
    cout << "Volumen: " << cilindro1.volumen() << endl;
    cilindro1.radio = 10;
    cilindro1.altura = 3;
    cout << "Volumen actualizado: " << cilindro1.volumen() << endl;
}