#include <iostream>
#include <vector>
#include <string>
#include <fstream> 

void print(std::vector <std::string>& v){
    for(int i = 0; i < v.size();i++){
        std::cout << v[i] << "\n";
    }
}

void split(std::string s, std::vector<std::string>& splitData, std::vector <std::string>& months,std::vector <std::string>& days, std::vector < std::vector <std::string> >& main){

	std::string temp = "";
	for(int i=0;i<s.length();++i){
		
		if(s[i]==' '){
			splitData.push_back(temp);
			temp = "";
		}
		else{
			temp.push_back(s[i]);
		}
		
	}
    splitData.push_back(temp);
    //std::cout << splitData.size() << "\n";
  
    if (splitData.size()<=9){
        months.push_back(splitData[0]);
        days.push_back(splitData[1]);
        main.push_back(months);
        main.push_back(days);
    }
    else{
        splitData.clear();  
    }

}  



void loadFile(std::vector <std::string>& data, std::vector <std::string>& splitData, std::vector <std::string>& months,std::vector <std::string>& days,std::vector < std::vector <std::string> >& main){
    std::string str;
    std::ifstream file("bitacora.txt");
    
    // Read the next line from File untill it reaches the end.

    while (std::getline(file, str))
    {
        split(str,splitData,months,days,main);
        
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0){
            data.push_back(str);
        }

    }

    
    //Close The File
    file.close();
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
    std::vector <std::string> splitData;
    std::vector <std::string> months;
    std::vector <std::string> days;
    std::vector < std::vector <std::string> > main;
    


    loadFile(data,splitData, months, days,main);
    //print(data);
    //print(splitData);
    print(days);
    //std::cout << main[0][1];





}