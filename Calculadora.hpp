#pragma once

class Calculadora {
private:
    double x;
    double y;
public:
    Calculadora();
    Calculadora(double, double);

    double suma();
    double multiplica();
    double resta();
    double divide();
};