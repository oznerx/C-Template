#include <iostream>
#include <vector>

//Mtricula
//Nombre

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


void busqBinaria(){

}

void busqSecuencial(){

}

int main()
{
    std::vector<int> vec;
    int n, low , mid, high;
    std::cout << "¿Cúantos datos quieres que tenga el vector?\n";
    std::cin >> n;

    for (int i = 0;i < n; i++){
        int num;
        std::cout << "Dame un número para la posición " << i+1 << ":\n";
        std::cin >> num;
        vec.push_back(num);  
    } 


    std::cout << "\n";
    std::cout << "El vector tiene los valores en el siguiente orden: \n";

    std::vector <int> ordenaI = ordenaIntercambio(vec,n);
    std::vector <int> ordenaB = ordenaBurbuja(vec,n);
    ordenaMerge(vec,0,n-1);



    for(auto i=0;i<vec.size();i++){
        std::cout << vec[i] << "\n";
    }


}