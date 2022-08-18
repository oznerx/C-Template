#include <iostream>
#include <vector>

//Mtricula
//Nombre

void ordenaIntercambio(std::vector<int> vec, int n){ 
    int i, j, aux; 
    for (i = 0 ; i <= n-2 ; i++){
        for (j = i+1 ; j <= n-1 ; j++){
            if (vec[i] > vec[j]){
                aux = vec[i];
                vec[i] = vec[j];
                vec[j]= aux ;
            }
        }
        std::cout << "a\n";
    } 
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

    ordenaIntercambio(vec,n);

    std::cout << "\n";
    std::cout << "El vector tiene los valores: \n";
    for(auto i=0;i<vec.size();i++){
        std::cout << vec[i] << "\n";
    }
}