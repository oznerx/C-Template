#include <iostream>


//Ozner Axel Leyva Mariscal 
//A01742377


int sumaIterativa(int n){
    int suma = 0;

    for (auto i= 1; i <= n;i++){
        suma += i;
    }

    return suma;
}


//Suma recursiva con complejidad de O(n)
int sumaRecursiva(int n){
    if (n != 0){
        return n + sumaRecursiva(n - 1);
    }
    return n;
}

//Suma directa con el metodo de Gauss para sumar números naturales 
int sumaDirecta(int n){
    return (n*(n + 1)/2);
}

int main(){
    int n;


    std::cout << "Dame un valor de n que sea positivo:\n";
    std::cin >> n;

    if (n>=0){
        std::cout << "El resultado con suma iterativa es de: " << sumaIterativa(n) << "\n";

        std::cout << "El resultado con suma Recursiva es de: " << sumaRecursiva(n) << "\n";

        std::cout << "El resultado con suma Direvta es de: " << sumaDirecta(n) << "\n";
    }
    else{
        std::cout << "El numero no es positivo\n";
    }

}

