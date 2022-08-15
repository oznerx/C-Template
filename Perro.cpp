#include "Perro.hpp"
#include <iostream>

Perro::Perro()
{
    peso= 20;
    edad = 5;
}

Perro::Perro(int edad, double peso) {
    edad = this->edad;
    peso = this->peso;
}

void Perro::salta() {
    std::cout << "el perro saltó\n";
    
}

