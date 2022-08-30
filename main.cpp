#include <iostream>
#include <vector>
#include <string>
#include <fstream> 

void print(std::vector <int>& v){ //test purpose
    for(int i = 0; i < v.size();i++){
        std::cout << v[i] << "\n";
    }
}

void split(std::string s, std::vector<std::string>& splitData, std::vector <std::string>& months,std::vector <std::string>& days,std::vector <std::string>& hour,std::vector <std::string>& ip,std::vector <std::string>& message){

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

    months.push_back(splitData[0]);
    days.push_back(splitData[1]);
    hour.push_back(splitData[2]);
    ip.push_back(splitData[3]);
    message.push_back(splitData[4] + " " + splitData[5] + " " +  splitData[6] + " " + splitData[7] + " " + splitData[8] + " " + splitData[9]);
    splitData.clear();  
    
}  

void loadFile(std::vector <std::string>& data, std::vector <std::string>& splitData, std::vector <std::string>& months,std::vector <std::string>& days,std::vector <std::string>& hour,std::vector <std::string>& ip,std::vector <std::string>& message){
    std::string str;
    std::ifstream file("bitacora.txt");
    
    // Read the next line from File untill it reaches the end.

    while (std::getline(file, str))
    {
        split(str,splitData,months,days,hour,ip,message);
        
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0){
            data.push_back(str);
        }

    }

    //Close The File
    file.close();
}

void datesToNum(std::vector <std::string>& months){
    
    for(int i = 0; i < months.size() ;i++){

        if(months[i] == "Jun"){
            months[i] = "6";
        }
        else if(months[i] == "Jul"){
            months[i] = "7";
        }
        else if(months[i] == "Aug"){
            months[i] = "8";
        }
        else if(months[i] == "Sep"){
            months[i] = "9";
        }
        else if(months[i] == "Oct"){
            months[i] = "10";
        }
        else{
            months[i] = "0000000"; //To identify some errors 
        }

    }

}

std::vector<int> getId(std::vector <std::string>& months,std::vector <std::string>& days){

    std::vector <int> ids;
    int id;
    for(int i = 0; i < months.size() ;i++){
        if(months[i] == "Jun"){
            id = stoi("6" + days[i]);
            ids.push_back(id);
        }
        else if(months[i] == "Jul"){
            id = stoi("7" + days[i]);
            ids.push_back(id);
        }
        else if(months[i] == "Aug"){
            id = stoi("8" + days[i]);
            ids.push_back(id);
        }
        else if(months[i] == "Sep"){
            id = stoi("9" + days[i]);
            ids.push_back(id);
        }
        else if(months[i] == "Oct"){
            id = stoi("10" + days[i]);
            ids.push_back(id);
        }
        else{
            ids.push_back(0000000); //To identify some errors 
        }
    }

    return ids;

}

void numToDates(std::vector <std::string>& data, std::vector <std::string>& months,std::vector <std::string>& days,std::vector <std::string>& hour,std::vector <std::string>& ip,std::vector <std::string>& message){
    
    for(int i = 0; i < months.size() ;i++){

        if(months[i] == "6"){
            months[i] = "Jun";
        }
        else if(months[i] == "7"){
            months[i] = "Jul";
        }
        else if(months[i] == "8"){
            months[i] = "Aug";
        }
        else if(months[i] == "9"){
            months[i] = "Sep";
        }
        else if(months[i] == "10"){
            months[i] = "Oct";
        }
        else{
            months[i] = "0000000"; //To identify some errors 
        }

    }

}

void sort(std::vector<std::string>& months,std::vector <std::string>& days,std::vector <std::string>& hour,std::vector <std::string>& ip,std::vector <std::string>& message){
    int i, j ; 
    std::string mAux;
    std::string dAux;
    std::string hAux;
    std::string ipAux;
    std::string messageAux;



    for (i = 0 ; i <= months.size()-2 ; i++){
        for (j = i+1 ; j <= months.size()-1 ; j++){
            if (std::stoi(months[i]) > std::stoi(months[j])){

                mAux = months[i];
                months[i] = months[j];
                months[j] = mAux;

                //falta hacer sort por días 

                dAux = days[i];
                days[i] = days[j];
                days[j] = dAux;

                hAux = hour[i];
                hour[i] = hour[j];
                hour[j] = hAux;

                ipAux = ip[i];
                ip[i] = ip[j];
                ip[j] = ipAux;   

                messageAux = message[i];
                message[i] = message[j];
                message[j] = messageAux;    
                         
            }
        }
    } 
}

void sortIds(std::vector<int>& ids){
    int i, j, aux; 

    for (i = 0 ; i <= ids.size()-2 ; i++){
        for (j = i+1 ; j <= ids.size()-1 ; j++){
            if (ids[i] > ids[j]){

                aux = ids[i];
                ids[i] = ids[j];
                ids[j] = aux;  

            }
        }
    }
}

void output(std::vector<std::string>& months,std::vector <std::string>& days,std::vector <std::string>& hour,std::vector <std::string>& ip,std::vector <std::string>& message){
  std::ofstream myfile ("bit.txt");
  if (myfile.is_open())
  {
    for(int i = 0; i < months.size();i++){
        myfile << months[i] + " " + days[i] + " " + hour[i] + " " + ip[i] + " " + message[i] << "\n";
    }
    myfile.close();
  }

  else std::cout << "Unable to open file";
}

void search(std::vector <int>& vec , int sDate, int eDate){
    for (int sDate;sDate < eDate;sDate++){
        std::cout << "This is my C++ gitpod template\n";
    }
}

int main()
{

/*
    Abra el archivo de entrada llamado "bitacora.txt Descargar bitacora.txt " lealo y almacene los datos en un vector.
    (Formato del archivo bitacora.pdf Descargar Formato del archivo bitacora.pdf).
    Ordene la información por fecha para la realización de las búsquedas.
    Solicite al usuario las fechas de inicio y fin de búsqueda de información.
    Despliegue los registros correspondientes a esas fechas.
    Almacenar en un archivo el resultado del ordenamiento.
*/

    std::vector <std::string> data;
    std::vector <std::string> splitData;
    std::vector <std::string> months;
    std::vector <std::string> days;
    std::vector <std::string> hour;
    std::vector <std::string> ip;
    std::vector <std::string> message;




    
    loadFile(data,splitData,months,days,hour,ip,message);
    //datesToNum(data,months,days,hour,ip,message);
    std::vector <int> ids = getId(months,days);
    sortIds(ids);
    print(ids);
    /*
    sort(months,days,hour,ip,message);
    numToDates(data,months,days,hour,ip,message);
    output(months,days,hour,ip,message);
    */

    
}