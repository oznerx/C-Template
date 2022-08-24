#include <iostream>
#include <vector>
#include <string>
#include <fstream> 

void split(std::string s, std::vector<std::string>& data){
	
    std::vector <std::string> date;
	std::string temp = "";

	for(int i=0;i<s.length();++i){
		
		if(s[i]==' '){
			date.push_back(temp);
			temp = "";
		}
		else{
			temp.push_back(s[i]);
		}
		
	}
	date.push_back(temp);
}

void SplitString(std::string s, std::vector<std::string> &v){
	
	std::string temp = "";
	for(int i=0;i<s.length();++i){
		
		if(s[i]==' '){
			v.push_back(temp);
			temp = "";
		}
		else{
			temp.push_back(s[i]);
		}
		
	}
	v.push_back(temp);
	
}

void loadFile(std::vector <std::string>& data){
    std::string str;
    std::ifstream file("bitacora.txt");
    std::vector <std::string> splitVector;
    std::string date;

    


    // Read the next line from File untill it reaches the end.

    while (std::getline(file, str))
    {
        SplitString(str,splitVector);

        splitVector[1] = date;

        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0){
            data.push_back(str);
        }
    }

    //Close The File
    file.close();
}

void print(std::vector <std::string>& v){
        for(int i = 0; i < v.size();i++){
        std::cout << v[i] << "\n";
    }
}





void search(std::vector <int>& vec , int sDate, int eDate){
    for (int sDate;sDate < eDate;sDate++){
        std::cout << "This is my C++ gitpod template\n";
    }
}

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

    loadFile(data);
    print(data);
    



}