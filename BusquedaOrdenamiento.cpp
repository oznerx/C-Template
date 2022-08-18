#include <iostream>
#include <vector>

//Nombre
//Matricula

std::vector<int> ordenaIntercambio(std::vector<int> vec, int n){ 
    int i, j, aux; 
    for (i = 0 ; i <= n-2 ; i++){
        for (j = i+1 ; j <= n-1 ; j++){
            if (vec[i] > vec[j]){
                aux = vec[i];
                vec[i] = vec[j];
                vec[j]= aux ;
            }
        }
    } 
    return vec;
}



std::vector<int> ordenaBurbuja(std::vector<int> vec, int n){
    int tmp;
    bool interruptor = true;
    for (int i = 0;i < n-1 && interruptor;i++){
        interruptor = false;
        for (int j = 0; j<n-1-i;j++){
            if(vec[j+1]<vec[j]){
                tmp = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = tmp;
                interruptor = true;
            }
        }
    }
    return vec;
}

void ordenaMergeIntervalos(std::vector<int>& vector,int s, int m, int e){
	std::vector<int> temp;

	int i, j;
	i = s;
	j = m + 1;

	while (i <= m && j <= e) {

		if (vector[i] <= vector[j]) {
			temp.push_back(vector[i]);
			++i;
		}
		else {
			temp.push_back(vector[j]);
			++j;
		}

	}

	while (i <= m) {
		temp.push_back(vector[i]);
		++i;
	}

	while (j <= e) {
		temp.push_back(vector[j]);
		++j;
	}

	for (int i = s; i <= e; ++i)
		vector[i] = temp[i - s];
}

void ordenaMerge(std::vector<int>& vector, int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		ordenaMerge(vector, s, m);
		ordenaMerge(vector, m + 1, e);
		ordenaMergeIntervalos(vector, s, m, e);
	}
}


int busqBinaria(std::vector<int>& vec, int low, int high, int num){

    while (low <= high) {

        int mid = low + (high - low) / 2;

        if (vec[mid] == num){
            return mid;
        }

        if (vec[mid] < num){
            low = mid + 1;
        }

        else{
            high = mid - 1;
        }
        
    }

    return -1;
}

int busqSecuencial(std::vector<int>& vector, int num){
    bool found = false;
    int location;
    for(location=0; location<vector.size(); location++)
    {
        if(vector.at(location) == num)
        {
            found = true;
            break;
        }
    }
    if(found)
    {
        return location;
    }
    else
    {
        return -1;
    }
}

int main()
{
    std::vector<int> vec;
    int n, low , mid, high, valor;
    std::cout << "¿Cúantos datos quieres que tenga el vector?\n";
    std::cin >> n;

    for (int i = 0;i < n; i++){
        int num;
        std::cout << "Dame un número para la posición " << i+1 << ":\n";
        std::cin >> num;
        vec.push_back(num);  
    } 

    std::cout << "\n";
    std::cout << "Utilizando el método de intercambio el vector tiene los valores en el siguiente orden : \n";
    for(auto i=0;i<ordenaIntercambio(vec,n).size();i++){
        std::cout << ordenaIntercambio(vec,n)[i] << "\n";
    }

    std::cout << "\n";
    std::cout << "Utilizando el método de burbuja el vector tiene los siguientes valores en el siguiente orden : \n";
    for(auto i=0;i<ordenaBurbuja(vec,n).size();i++){
        std::cout << ordenaBurbuja(vec,n)[i] << "\n";
    }

    std::cout << "\n";
    std::cout << "Utilizando el método de merge el vector tiene los valores en el siguiente orden : \n";
    ordenaMerge(vec,0,n-1);    
    for(auto i=0;i<vec.size();i++){
        std::cout << vec[i] << "\n";
    }

    std::cout << "Dame un valor a buscar en el vector\n";
    std::cin >> valor;
    low = 0;
    high = vec.size();
    std::cout << "Utilizando la busqueda secuencial el numero se encuentra en la posición  " << busqSecuencial(vec,valor) << " del vector (iniciando en 0)\n";
    std::cout << "Utilizando la busqueda binaria el numero se encuentra en la posición  " << busqBinaria(vec,0,vec.size(),valor) << " del vector (iniciando en 0)\n";


}