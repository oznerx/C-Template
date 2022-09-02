/* 
	TODO:
	[ ] Poner un algoritmo de sorting que no sea lento (actualmente bubble sort sube el uso de CPU al 100%)
	[ ] Completar el método getLogMessagesBetweenDates()
	[ ] Agregar comentarios de time complexities y header con nuestros nombres
	[ ] Hacer pruebas para ver si funciona
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void print(vector <string>& v){
	for (int i = 0 ; i < v.size() ;i++){
		cout << v[i] << "\n";
	}
}

int main() {
	vector <string> months;
	vector <string> days;
	vector <string> times;
	vector <string> ips;
	vector <string> messages;

	ifstream inputFile("bitacora.txt");
	string month, day, time, ip, message;
			
	while(inputFile >> month >> day >> time >> ip) {
		inputFile.get();
		getline(inputFile, message);

		months.push_back(month);
		days.push_back(day);
		times.push_back(time);
		ips.push_back(ip);
		messages.push_back(message);

	}
	print(messages);
}



