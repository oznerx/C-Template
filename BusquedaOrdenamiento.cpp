#include <iostream>
#include <vector>

/*
Ozner Axel Leyva Mariscal
A01742377
*/

/*Descripción*/
void ordenaIntercambio(std::vector<int>& vec, int n){ 
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
}

/**/
void ordenaBurbuja(std::vector<int>& vec, int n){
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
}


/**/
void ordenaMergeIntervalos(std::vector<int>& vector,int low, int mid, int high){
	std::vector<int> temp; 

	int i, j;
	i = low;
	j = mid + 1;

	while (i <= mid && j <= high) {

		if (vector[i] <= vector[j]) {
			temp.push_back(vector[i]);
			++i;
		}
		else {
			temp.push_back(vector[j]);
			++j;
		}

	}

	while (i <= mid) {
		temp.push_back(vector[i]);
		++i;
	}

	while (j <= high) {
		temp.push_back(vector[j]);
		++j;
	}

	for (int i = low; i <= high; ++i)
		vector[i] = temp[i - low];
}

/**/ 
void ordenaMerge(std::vector<int>& vector, int low, int high) {
	if (low < high) { 
		int mid = (low + high) / 2;  
		ordenaMerge(vector, low, mid); 
		ordenaMerge(vector, mid + 1, high); 
		ordenaMergeIntervalos(vector, low, mid, high);
	}
}

/**/
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

/**/
int busqSecuencial(std::vector<int>& vector, int num){
    bool found = false;
    int i; 
    for(i=0; i<vector.size(); i++)
    {
        if(vector.at(i) == num)
        {
            found = true;
            break;
        }
    }
    if(found)
    {
        return i; 
    }
    else
    {
        return -1;
    }
}

/**/
void print(std::vector<int>& vec){
    for(auto i=0;i<vec.size();i++){
        std::cout << vec[i] << "\n";
    }
}

int main() 
{
    int valor = 7;

    std::cout << "\n";
    std::cout << "Los valores predeterminados del vector de prueba 1 son son los siguientes: \n";
    std::vector<int> vec1 = {8, 5, 1, 4, 3, 7, 6 }; 
    print(vec1);

    std::cout << "\n";
    std::cout << "Utilizando el método de intercambio, el vector tiene los valores en el siguiente orden: \n";
    ordenaIntercambio(vec1,vec1.size());
    print(vec1);

    std::cout << "\n";
    std::cout << "Los valores predeterminados del vector de prueba 2 son son los siguientes: \n";
    std::vector<int> vec2 = {2, 9, 3, 4, 1, 7, 5 }; 
    print(vec2);

    std::cout << "\n";
    std::cout << "Utilizando el método de burbuja, el vector tiene los siguientes valores en el siguiente orden: \n";
    ordenaBurbuja(vec2, vec2.size());
    print(vec2);

    std::cout << "\n";
    std::cout << "Los valores predeterminados del vector de prueba 3 son son los siguientes: \n";
    std::vector<int> vec3 = {5, 9, 7, 4, 2, 4, 1 }; 
    print(vec3);

    std::cout << "\n";
    std::cout << "Utilizando el método de merge, el vector tiene los valores en el siguiente orden: \n";
    ordenaMerge(vec3,0,vec3.size()-1);    
    print(vec3);

    std::cout << "\n";
    std::cout << "Utilizando la busqueda secuencial, el número '7' se encuentra en la posición  " << busqSecuencial(vec3,valor) << " del vector de prueba 3 \n";
    std::cout << "\n";
    std::cout << "Utilizando la busqueda binaria, el número '7' se encuentra en la posición  " << busqBinaria(vec3,0,vec3.size(),valor) << " del vector de prueba 3\n";
    std::cout << "\n";
}