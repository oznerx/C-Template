#include <iostream>
#include <vector>

//Nombre
//Matricula

//Se crea una función que retorna el otro vector con los mismos valores que el introducido pero ya esta ordenado con el método de Intercambio
//Es de orden O(n^2)
std::vector<int> ordenaIntercambio(std::vector<int> vec, int n){ 
    int i, j, aux; /* se realizan n-1 pasadas, vec[o] ... vec[n-2] */
    for (i = 0 ; i <= n-2 ; i++){ /* coloca mínimo de vec[i+1]...vec[n-1] en vec[i] */
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

//Se crea una función que retorna el otro vector con los mismos valores que el introducido pero ya esta ordenado con el método de Burbuja
// En el mejor caso es de O(n)
//En el peor caso es de O(n^2)
std::vector<int> ordenaBurbuja(std::vector<int> vec, int n){
    int tmp; //Variable temporal
    bool interruptor = true; //Para saber cuando acabar el ciclo
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
    return vec; //se retorna el nuevo vector ya ordenado
}


//Creamos una funcion con la que manejamos los intervalos para depues acomodar los números 
void ordenaMergeIntervalos(std::vector<int>& vector,int low, int mid, int high){
	std::vector<int> temp; //Creamos un vector temporal 

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

//Creamos una función para utilizar los limites 
//La funcion es void porque utilizamor apuntadores 
void ordenaMerge(std::vector<int>& vector, int low, int high) {
	if (low < high) { // Verificamos que los limites son posibles 
		int mid = (low + high) / 2; //obtenemos el valor de la mitad 
		ordenaMerge(vector, low, mid); //llamamos la parte inferior
		ordenaMerge(vector, mid + 1, high); //llamamos la parte superior
		ordenaMergeIntervalos(vector, low, mid, high);
	}
}

//Creamos una funcion de busqueda binaria para buscar por mitades 
int busqBinaria(std::vector<int>& vec, int low, int high, int num){

    while (low <= high) { // Verificamos que los limites sean posibles 

        int mid = low + (high - low) / 2; //obtenemos la mitad 

        if (vec[mid] == num){ //si se encuentra el valor se retorna
            return mid;
        }

        if (vec[mid] < num){ //si no se encuentra el valor se va a la mitad superior 
            low = mid + 1;
        }

        else{
            high = mid - 1; //si no se encuentra el valor se va a la mitad inferior
        }
        
    }

    return -1;
}

//Creamos una función para buscar secuencialmente
int busqSecuencial(std::vector<int>& vector, int num){
    bool found = false; //Variable para saber cuando ya encontramos a nuestro objetivo 
    int i; //se crea una variable donde guardaremos la ubicación de lo que queremos encontrar 
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
        return i; //Cuando se encuentra el objetivo se retorna la posición en la que se encuentra
    }
    else
    {
        return -1;
    }
}

int main()
{
    std::vector<int> vec; //Declaració del vector a utilizar 
    int n, low , mid, high, valor;
    std::cout << "¿Cúantos datos quieres que tenga el vector?\n";
    std::cin >> n;

    for (int i = 0;i < n; i++){ //Se recorre el vector para agragar valores 
        int num;
        std::cout << "Dame un número para la posición " << i << ":\n";
        std::cin >> num;
        vec.push_back(num);  
    } 

    std::cout << "\n";
    std::cout << "Utilizando el método de intercambio el vector tiene los valores en el siguiente orden : \n";
    for(auto i=0;i<ordenaIntercambio(vec,n).size();i++){ //Se recorre el nuevo vector para ir mostrando valor por valor 
        std::cout << ordenaIntercambio(vec,n)[i] << "\n";
    }

    std::cout << "\n";
    std::cout << "Utilizando el método de burbuja el vector tiene los siguientes valores en el siguiente orden : \n";
    for(auto i=0;i<ordenaBurbuja(vec,n).size();i++){ //Se recorre el nuevo vector para ir mostrando valor por valor 
        std::cout << ordenaBurbuja(vec,n)[i] << "\n";
    }

    std::cout << "\n";
    std::cout << "Utilizando el método de merge el vector tiene los valores en el siguiente orden : \n";
    ordenaMerge(vec,0,n-1);    //Se utiliza la función para ordenar el vector ya existente 
    for(auto i=0;i<vec.size();i++){ //Se recorre el nuevo vector para ir mostrando valor por valor
        std::cout << vec[i] << "\n";
    }

    std::cout << "\n";
    std::cout << "Dame un valor a buscar en el vector\n";
    std::cin >> valor;
    low = 0;
    high = vec.size();
    std::cout << "\n";
    std::cout << "Utilizando la busqueda secuencial el numero se encuentra en la posición  " << busqSecuencial(vec,valor) << " del vector (iniciando en 0)\n";
    std::cout << "Utilizando la busqueda binaria el numero se encuentra en la posición  " << busqBinaria(vec,0,vec.size(),valor) << " del vector (iniciando en 0)\n";

}