#include <iostream>
#include <unordered_map>

  
int main()
{
    // Declaring umap to be of <string, int> type
    // key will be of string type and mapped value will
    // be of int type
    std::unordered_map< int , std::string> listaSuper = {
        {1, "huevos"}, {2, "leche"}, {3, "tortillas"}
    };
  
    // inserting values by using [] operator
    listaSuper[4] = "cereal";
  
    // Traversing an unordered map
    for (auto x : listaSuper){
        std::cout << x.first << " " << x.second << "\n" ;
    }  

    int num;
    std::cout << "hasta que numero quieres la lista?\n";
    std::cin >> num;
    for ( auto x : listaSuper){
        if (x.first < num + 1){
            std::cout << x.first << " " << x.second << "\n";
        }
    }
    /*
    for (int i = 0;i < listaSuper[3];i++){
        std::cout << "-----------" <<listaSuper[num];
    }
    */

}