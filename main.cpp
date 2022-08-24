#include <iostream>
#include <vector>
#include <string>
#include <fstream> 

void loadFromFile(std::vector <std::string>& data){
    std::string str;
    std::ifstream file("bitacora.txt");


    // Read the next line from File untill it reaches the end.

    while (std::getline(file, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0){
            data.push_back(str);
        }
    }

    //Close The File
    file.close();
}
/*
void split (std::vector <std::string> splitVector, std::string seperator){


    for (int x=0;x<=9;x++)
    {
        splitVector[x]="";
    }

    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  

    while (i <= splitVector.size())  
    {  
        if (splitVector[i] == seperator || i == splitVector.size())  
        {  
            endIndex = i;  
            std::string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            splitVector[currIndex] = subStr;  
            currIndex += 1;  
            startIndex = endIndex + 1;  
        }  
        i++;  
    }  
}

void search(std::vector <int>& vec , int sDate, int eDate){
    for (int sDate;sDate < eDate;sDate++){
        std::cout << "This is my C++ gitpod template\n";
    }
}
*/
int main()
{
/*
    Abra el archivo de entrada llamado "bitacora.txt Descargar bitacora.txt " lealo y almacene los datos en un vector  (Formato del archivo bitacora.pdf Descargar Formato del archivo bitacora.pdf ).
    Ordene la información por fecha para la realización de las búsquedas.
    Solicite al usuario las fechas de inicio y fin de búsqueda de información.
    Despliegue los registros correspondientes a esas fechas.
    Almacenar en un archivo el resultado del ordenamiento.
*/

    std::vector <std::string> data;
    loadFromFile(data);

    std::cout << "This is my C++ gitpod template\n";
    
    for(int i = 0; i < data.size();i++){
        std::cout << data[i] << "\n";
    }


}