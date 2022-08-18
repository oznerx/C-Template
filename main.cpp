#include <iostream>
#include <vector>

//Mtricula
//Nombre

void ordenaIntercambio(){

}

void ordenaBurbuja(){
    
}

void ordenaMerge(){
    
}

void busqSecuencial(){
    
}

void busqBinaria(){
    
}

int main()
{
    std::vector<int> vec;
    int n;
    std::cout << "¿Cúantos datos quieres que tenga el vector?\n";
    std::cin >> n;

    for (int i = 0;i < n; i++){
        int num;
        std::cout << "Dame un número: \n";
        std::cin >> num;
        vec.insert(i,num);  
    } 
}