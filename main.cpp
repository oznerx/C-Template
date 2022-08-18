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
        std::cout << "Dame un número para la posición " << i+1 << ":\n";
        std::cin >> num;
        vec.push_back(num);  
    } 
    
    std::cout << "\n";
    std::cout << "El vector tiene los valores: \n";
    for(auto i=0;i<vec.size();i++){
        std::cout << vec[i] << "\n";
    }
}