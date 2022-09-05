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
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

unordered_map<string, int> MONTH_INDEXES = {
	{"Jan", 0}, {"Feb", 1}, {"Mar", 2}, {"Apr", 3}, {"May", 4}, 
	{"Jun", 5}, {"Jul", 6}, {"Aug", 7}, {"Sep", 8}, {"Oct", 9}, 
	{"Nov", 10}, {"Dec", 11},
};

vector<int> MONTH_DAYS = {31,28,31,30,31,30,31,31,30,31,30,31};

class Date {
	string month;
	string day;
	string time;
	int secondsSinceStartOfYear;

	int getDaysSinceStartOfYear() {
		int daysSinceStartOfYear = 0;
		
		for(int i = 0; i<MONTH_INDEXES[this->month]; i++){
			daysSinceStartOfYear += MONTH_DAYS[i];
		}
		
		return daysSinceStartOfYear + stoi(day);
	}

	void calculateSecondsSinceStartOfYear() {
		int days = getDaysSinceStartOfYear();
		int hours = stoi(time.substr(0,2));
		int minutes = stoi(time.substr(3,2));
		int seconds = stoi(time.substr(6,2));

		this->secondsSinceStartOfYear = ((days * 24 + hours) * 60 + minutes) * 60 + seconds;
	}

	public:
		Date(string month, string day, string time) {
			this->month = month;
			this->day = day;
			this->time = time;
			this->calculateSecondsSinceStartOfYear();
		}

		int getSecondsSinceStartOfYear() {
			return this->secondsSinceStartOfYear;
		}

		bool operator > (Date anotherDate) {
			return this->getSecondsSinceStartOfYear() > anotherDate.getSecondsSinceStartOfYear();
		}

		friend ostream &operator << (ostream &output, Date date) {
			output << date.month << " " << date.day << " "<< date.time;
			return output;
		}

};

class LogMessage {
	Date date;
	string ip;
	string info;

	public:
		LogMessage(string month, string day, string time, string ip, string info) : date(month, day, time) {
			this->ip = ip;
			this->info = info;
		}

		Date getDate() {
			return this->date;
		}

		friend ostream &operator << (ostream &output, LogMessage logMessage) {
			output << logMessage.date << " " << logMessage.ip << " " << logMessage.info;
			return output;
		}

};

class LogMessagesManager {
	vector<LogMessage> logMessages;

	public:
		LogMessagesManager() {
			
		}

		void read(string inputFilePath) {
			ifstream inputFile(inputFilePath);
			string month, day, time, ip, info;
			
			while(inputFile >> month >> day >> time >> ip) {
				inputFile.get();
				getline(inputFile, info);
	
				LogMessage* logMessage = new LogMessage(month, day, time, ip, info);
				logMessages.push_back(*logMessage);
			}
	
			inputFile.close();
		}
/*
		void sort() {
			for(int i=0; i<logMessages.size(); i++) {
				bool isOrdered = true;
				
				for(int j=1; j<logMessages.size()-i; j++) {
					if(logMessages[j-1].getDate() > logMessages[j].getDate()) {
						swap(logMessages[j-1], logMessages[j]);
						isOrdered = false;
					}
				}
	
				if (isOrdered) {
					return;
				}
			}
		}
*/	
		int partition(vector<LogMessage> &v, int left, int right) {
			int pivotIndex = left + (right - left) / 2;
			int pivotValue = v[pivotIndex].getDate().getSecondsSinceStartOfYear();
			int i = left, j = right;
			int temp;
			while(i <= j) {
				while(v[i].getDate().getSecondsSinceStartOfYear() < pivotValue) {
					i++;
				}
				while(v[j].getDate().getSecondsSinceStartOfYear() > pivotValue) {
					j--;
				}
				if(i <= j) {
					temp = v[i].getDate().getSecondsSinceStartOfYear();
					v[i] = v[j];
					v[j] = temp;
					i++;
					j--;
				}
			}
			return i;
		}

		void quicksort(vector<LogMessage> &v, int left, int right) {
			if(left < right) {
				int pivotIndex = partition(v, left, right);
				quicksort(v, left, pivotIndex - 1);
				quicksort(v, pivotIndex, right);
			}
		}
	

		vector<LogMessage> getLogMessagesBetweenDates(Date startDate, Date endDate) {
			vector<LogMessage> results;
			
			return results;
		}

		void save(string outputFilePath) {
			ofstream outputFile(outputFilePath);

			for(LogMessage logMessage : logMessages) {
				outputFile << logMessage << "\n";
			}

			outputFile.close();
		}
		void sort() {
			quicksort(logMessages, 0, logMessages.size() - 1);
		}
};


int main() {
	LogMessagesManager* logMessagesManager = new LogMessagesManager();
	logMessagesManager->read("bitacora.txt");
	
	cout << "Ordenando..." << "\n";
	logMessagesManager->sort();

	cout << "===Intoduzca fechas para la búsqueda===" << "\n";
	cout << "Ejemplo: Oct 13 07:01:33" << "\n\n";

	string month, day, hour;
	
	cout << "Fecha 1: ";
	cin >> month >> day >> hour;
	Date* startDate = new Date(month, day, hour);

	cout << "Fecha 2: ";
	cin >> month >> day >> hour;
	Date* endDate = new Date(month, day, hour);

	vector<LogMessage> results = logMessagesManager->getLogMessagesBetweenDates(*startDate, *endDate);

	cout << "===Resultados===" << "\n";
	for(LogMessage logMessage : results) {
		cout << logMessage << "\n";
	}
	
	logMessagesManager->save("bitacora_ordenada.txt");
}

/* 
Referencias:
https://www.w3schools.com/cpp/cpp_classes.asp
https://www.w3schools.com/cpp/cpp_access_specifiers.asp
https://stackoverflow.com/questions/7663709/how-can-i-convert-a-stdstring-to-int
https://cplusplus.com/reference/string/string/substr/
https://stackoverflow.com/questions/15151480/simple-dictionary-in-c
https://www.geeksforgeeks.org/map-vs-unordered_map-c/
https://www.geeksforgeeks.org/object-composition-delegation-in-c-with-examples/
https://www.tutorialspoint.com/cplusplus/relational_operators_overloading.htm
https://www.learncpp.com/cpp-tutorial/overloading-the-comparison-operators/
https://www.w3schools.com/cpp/cpp_files.asp
https://www.geeksforgeeks.org/cpp-program-read-file-word-word/
https://stackoverflow.com/questions/3263323/c-read-from-istream-until-newline-but-not-whitespace
https://www.geeksforgeeks.org/how-to-iterate-through-a-string-word-by-word-in-c/
https://stackoverflow.com/questions/2462951/c-equivalent-of-stringbuffer-stringbuilder
https://stackoverflow.com/questions/12240010/how-to-read-from-a-text-file-character-by-character-in-c
https://en.wikipedia.org/wiki/Whitespace_character
https://stackoverflow.com/questions/7623650/resetting-a-stringstream
https://www.loginradius.com/blog/engineering/eol-end-of-line-or-newline-characters/
https://www.tutorialspoint.com/cpp_standard_library/cpp_vector_clear.htm#:~:text=The%20C%2B%2B%20function%20std%3A%3A,size%20of%20vector%20to%20zero
https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
https://cplusplus.com/forum/beginner/13866/
https://cplusplus.com/reference/istream/istream/ignore/
https://www.w3schools.com/cpp/cpp_files.asp
https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
https://www.tutorialspoint.com/cplusplus/input_output_operators_overloading.htm
*/

