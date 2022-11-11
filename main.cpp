#include <iostream>
#include <vector>
using namespace std;

struct Arista {
    int origen, destino;
};

class Grafo
{
public:
    vector<vector<int>> adyacencias;

    /*
     Construye un grafo de n vertices recibiendo un vector de aristas
     @param vector<Arista> const& aristas: vecotor con aristas
     @param int n: cantidad de nodos
    */
    Grafo(vector<Arista> const& aristas, int n)
    {
        adyacencias.resize(n);
        for (Arista arista : aristas)
        {
            int origen = arista.origen;
            int destino = arista.destino;
            adyacencias[origen].push_back(destino);
            adyacencias[destino].push_back(origen);
        }
    }

};

/*
* Imprime ruta
*/
void imprimirRuta(vector<int> const& ruta)
{
    for (int i : ruta) {
        cout << i << ' ';
    }
    cout << endl;
}

void caminosHamiltonianos(Grafo const& grafo, int nodoActual, vector<bool>& visitados, vector<int>& ruta, int n)
{
    if (ruta.size() == n) {

        imprimirRuta(ruta);
        
        for (int j = 0 ; j < grafo.adyacencias[nodoActual].size(); j++ ) {
            
            if ( grafo.adyacencias[nodoActual][j] == ruta[0]) {
                cout << "Es un ciclo\n";
            }

        }

        return;
    }

    for (auto i : grafo.adyacencias[nodoActual]) {
        visitados[i] = true;
        ruta.push_back(i);
        caminosHamiltonianos(grafo, i, visitados, ruta, n);
        visitados[i] = false;
        ruta.pop_back();
    }

}

void GeneraCaminosHamiltonianos(Grafo const& grafo, int n)
{
    vector <bool> visitados(n,false);

    vector <int> ruta;

    for (auto i = 0; i < n ;i++) {

        visitados[i] = true;
        ruta.push_back(i);
        caminosHamiltonianos(grafo, i,  visitados, ruta, n);
        visitados[i] = false;
        ruta.pop_back();

    }


}

int main()
{
    int n = 5;
    vector<Arista> aristas = {
        {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3},{4,3}, {4,0}
    };
    Grafo grafo(aristas, n);
    GeneraCaminosHamiltonianos(grafo, n);
    return 0;
}