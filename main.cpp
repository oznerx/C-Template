#include <iostream>


//Ozner Axel Leyva Mariscal 
//A01742377

//Función con suma iterativa 
//Complejidad de O(n)
int sumaIterativa(int n){
    int suma = 0; //Es la variable donde se van sumado los números 

    for (auto i= 1; i <= n;i++){
        suma += i;
    }

    return suma;
}


//Función de suma recursiva 
//Complejidad de O(log n)
int sumaRecursiva(int n){
    if (n >= 1){ //Se llama a si mismo mientras n sea mayor o igual a 1 
        return n + sumaRecursiva(n - 1); //Se van sumando los números desde n hasta 1 
    }
    return n;
}

//Función de suma directa con el metodo de Gauss para sumar números naturales
//Complejidad de O(1)
int sumaDirecta(int n){
    return (n*(n + 1)/2); //Método de Gauss
}

int main(){
    int n = 5;

    /* Por si se quiere pedir el valor de n en terminal 
    std::cout << "Dame un valor de n que sea entero positivo:\n";
    std::cin >> n;
    */

    std::cout << "Tu valor de n es de " << n << "\n";

    if (n>=0){ //Para evitar numeros negativos 
        std::cout << "El resultado de la suma de 1 hasta n sumando iterativamente es de " << sumaIterativa(n) << "\n";

        std::cout << "El resultado de la suma de 1 hasta n sumando Recursivamente es de " << sumaRecursiva(n) << "\n";

        std::cout << "El resultado de la suma de 1 hasta n sumando Directamente es de " << sumaDirecta(n) << "\n";
    }
    else{
        std::cout << "El numero no es positivo\n";
    }

}

