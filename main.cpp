#include <iostream>
#include <string>
#include "List.h"
//#include "MyString.h"
using namespace std;
int height;
int width;
bool isOnMap(int x, int y) {
	if (x >= 0 && y >= 0 && y < height && x < width) {
		return true;
	}
	else return false;
}

bool findLetter(int x, int y, char** map) {
	//if(map[x][y] != '*' && map[x][y] != '.' && map[x][y] != '#'){
	if (isOnMap(x, y)) {
		if ((map[x][y] >= '0' && map[x][y] <= '9') || (map[x][y] >= '65' && map[x][y] <= '90')) {
			return true;
		}
		else return false;
	}
	return false;
}

string findCityName(int x, int y, char** map) {
	//mamy jakas litere na miejscu x y
	string tmp;
	char litera;
	int x1=x;
	
	//szukamy poczatku wyrazu
	//koniec mapy?
	//if (x1 != 0&&map[x1 - 1][y] != '*' && map[x1 - 1][y] != '.' && map[x1 - 1][y] != '#') {

	if(findLetter(x1 - 1, y, map)) {
		x1--;
	}
	else {
		for (int i = x1; i < x; i++) {
			tmp += map[i][y];
		}
	}
	//koniec wyrazu
	//konec mapy????
	if (map[x1 + 1][y] != '*' && map[x1 + 1][y] != '.' && map[x1 + 1][y] != '#') {
		x1++;
	}
	else {
		for (int i = x; i < x1; i++) {
			tmp += map[i][y];
		}
	}
	return tmp;
	
}
struct city {
	string name;
	int pozX;
	int pozY;
};
struct flight {
	string start;
	string destination;
	int time;
};
struct question {
	string town1;
	string town2;
	int type;
};

int main() {
	    //tab[width][height]
	int flightCounter; //liczba polaczen lotniczych
	// zrodlo cel czas
	//zrodlo - miasto poczatkowe
	//cel - miasto koncowe

	//zrodlo cel typ
	// pyta o najkrotszy czas przejazdu z ZRODLA do CELU 
	//TYP=0 - tylko czas
	//TYP=1 - czas i trasa

	cin >> height;
	cin >> width;


	char** map = new char* [width];
	for (int i = 0; i < width; i++) {
		map[i] = new char[height];
	}
	//char znak;
	//znak = getchar();
	// wczytanie wartoœci do tablicy
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			//map[i][j] = znak;
			cin >> map[i][j];
		}
	}

	cin >> flightCounter;
	flight* plane = new flight[flightCounter];

	for (int i = 0; i <flightCounter; i++) {
		cin >> plane[i].start;
		cin >> plane[i].destination;
		cin >> plane[i].time;
	}

	//questCounter = 2;
	int questCounter; 
	cin >> questCounter;
	question* quest = new question[questCounter];
	for (int i = 0; i < questCounter; i++) {
		cin >> quest[i].town1;
		cin >> quest[i].town2;
		cin >> quest[i].type;
	}

	for (int n = 0; n < questCounter; n++) {
		//zapisywanie miast do listy
		MyList <city> cities;
		//1. przejsc po mapie i znalezc gwiazdke 
		//2. zapiac koordynaty gwiazdki
		//3. znalezc literke lub cyfre wokol gwiazdki
		//4. przechodzic w lewo i prawo po tablicy szukajac konca i poczatku wyrazu
		
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				//szukanie gwiazdki z kazdej strony 
				if (map[i][j] == '*') {
					city c;
					c.pozX = i;
					c.pozY = j;
					//c->name = ".";
					//while(c->name=="."){ 
					if(findLetter(i - 1, j, map)) { c.name = findCityName(i - 1, j, map); }
					else if (findLetter(i + 1, j, map)) { c.name = findCityName(i + 1, j, map); }
					else if (findLetter(i, j - 1, map)) { c.name = findCityName(i, j - 1, map); }
					else if (findLetter(i, j + 1, map)) { c.name = findCityName(i, j + 1, map); }
					else if (findLetter(i + 1, j + 1, map)) { c.name = findCityName(i + 1, j + 1, map); }
					else if (findLetter(i - 1, j - 1, map)) { c.name = findCityName(i - 1, j - 1, map); }
					else if (findLetter(i + 1, j - 1, map)) { c.name = findCityName(i + 1, j - 1, map); }
					else if (findLetter(i - 1, j + 1, map)) { c.name = findCityName(i - 1, j + 1, map); }
				//	} 
					cities.add(c);

					cout << c.name << endl;
				}
			}
		}
	}

	/*cout << map[14][0] << endl;
	cout << map[0][14] << endl;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			cout<< map[j][i];
		}
		cout << endl;
	}*/

	return 0;
}