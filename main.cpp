#include <iostream>
#include <string>
#include "List.h"
//#include "MyString.h"
using namespace std;

struct city {
	string name;
	int pozX;
	int pozY;
};

struct trip {
	string start;
	string destination;
	int time;
};

struct question {
	string town1;
	string town2;
	int type;
};

struct coordinates {
	int x;
	int y;
};

bool operator==(const coordinates& k1, const coordinates& k2)
{
	if (k1.x == k2.x && k1.y == k2.y) return true;
	return false;
}

std::ostream& operator<<(std::ostream& os, const coordinates& k) {
	os << k.x << ", " << k.y << endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const trip& k) {
	os << k.start << ", " << k.destination << ", " << k.time << endl;
	return os;
}

//struct coordinatesWithCounter {
//	int counter;
//	coordinates coordinates;
//};

int height;
int width;
MyList <city> cities;

bool isOnMap(int x, int y) {
	if (x >= 0 && y >= 0 && y < height && x < width) {
		return true;
	}
	else return false;
}

bool findLetter(int x, int y, char** map) {
	//if(map[x][y] != '*' && map[x][y] != '.' && map[x][y] != '#'){
	if (isOnMap(x, y)) {
		if ((map[x][y] >= '0' && map[x][y] <= '9') || (map[x][y] >= 'A' && map[x][y] <= 'Z')) {
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

	while(findLetter(x1 - 1, y, map)) {
		x1--;
	}

	for (int i = x1; i < x; i++) {
		tmp += map[i][y];
	}
	x1 = x;
	//koniec wyrazu
	//konec mapy????
	while (findLetter(x1 + 1, y, map)) {
		x1++;
	}
	
	for (int i = x; i <= x1; i++) {
		tmp += map[i][y];
	}
	
	return tmp;
}


void search(city firstCity, coordinates current, MyList<coordinates>& visited, MyList<trip>& foundTrips, char** map, int distance = 0) {
	visited.add(current);

	coordinates coordinatesToCheck[] = {
		{current.x, current.y - 1}, 
		{current.x, current.y + 1},
		{current.x - 1, current.y},
		{current.x + 1, current.y}
	};

	for (int j = 0; j < 4; j++) {
		coordinates newCoords = coordinatesToCheck[j];
		if (isOnMap(newCoords.x, newCoords.y)) {
			char character = map[newCoords.x][newCoords.y];
			if (visited.find(newCoords) == nullptr) { //czemu sprawdzamy czy nullptr???
				visited.add(newCoords); //dodajemy koordynaty do odwiedzonych

				if (character == '#') {
					search(firstCity, newCoords, visited, foundTrips, map, distance + 1);
				}
				else if (character == '*') { //znalezlismy miasto
					trip t; //dodajemy polaczenie do listy polaczen
					t.start = firstCity.name;
					for (int i = 0; i < cities.size(); i++) {
						city c = cities.valueAt(i);
						if (c.pozX == newCoords.x && c.pozY == newCoords.y) {
							t.destination = c.name;
							break;
						}
					}
					t.time = distance;
					foundTrips.add(t);
				}
			}
		}
	}
	/*if (isOnMap(current.x, current.y - 1)) {
		char character = map[current.x][current.y - 1];
		coordinates newCoords = { current.x, current.y - 1 };
		if (visited.find(newCoords) == nullptr) {
			visited.add(newCoords);

			if (character == '#') {
				search(firstCity, newCoords, visited, foundTrips, map, distance + 1);
			}
			else if (character == '*') {
				trip t;
				t.start = firstCity.name;
				for (int i = 0; i < cities.size(); i++) {
					city c = cities.valueAt(0);
					if (c.pozX == current.x && c.pozY == current.y) {
						t.destination = c.name;
						break;
					}
				}
				t.time = distance;
				foundTrips.add(t);
			}
		}
	}
	if (isOnMap(current.x, current.y + 1)) {
		map[current.x][current.y + 1];

	}
	if (isOnMap(current.x - 1, current.y)) {
		map[current.x - 1][current.y];

	}
	if (isOnMap(current.x + 1, current.y)) {
		map[current.x + 1][current.y];

	}*/
}

int main() {
	MyList <trip> trips;
	int flightCounter; //liczba polaczen lotniczych
	int questCounter; //liczba zapytan

	cin >> height;
	cin >> width;

	char** map = new char* [height];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width];
	}
	
	// wczytanie wartoœci do tablicy
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			cin >> map[j][i];
		}
	}

	cin >> flightCounter;

	for (int i = 0; i < flightCounter; i++) {
		trip plane;

		cin >> plane.start;
		cin >> plane.destination;
		cin >> plane.time;

		trips.add(plane); // dodajemy lot do listy mozliwych przejazdow 
	}

	cin >> questCounter;
	question* quest = new question[questCounter];
	for (int i = 0; i < questCounter; i++) {
		cin >> quest[i].town1;
		cin >> quest[i].town2;
		cin >> quest[i].type;
	}

	//zapisywanie miast do listy
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			//szukanie gwiazdki z kazdej strony 
			if (map[i][j] == '*') {
				city c;
				c.pozX = i;
				c.pozY = j;

				if (findLetter(i - 1, j, map)) { c.name = findCityName(i - 1, j, map); }
				else if (findLetter(i + 1, j, map)) { c.name = findCityName(i + 1, j, map); }
				else if (findLetter(i, j - 1, map)) { c.name = findCityName(i, j - 1, map); }
				else if (findLetter(i, j + 1, map)) { c.name = findCityName(i, j + 1, map); }
				else if (findLetter(i + 1, j + 1, map)) { c.name = findCityName(i + 1, j + 1, map); }
				else if (findLetter(i - 1, j - 1, map)) { c.name = findCityName(i - 1, j - 1, map); }
				else if (findLetter(i + 1, j - 1, map)) { c.name = findCityName(i + 1, j - 1, map); }
				else if (findLetter(i - 1, j + 1, map)) { c.name = findCityName(i - 1, j + 1, map); }

				cities.add(c); //dodanie miasta do tablicy
			}
		}
	}

	//szukanie najkrotszej drogi
	for (int i = 0; i < questCounter; i++) {
		//ile miast polaczonych jest z PIERWSZYM 
		//ile trwaja dystanse (dlugosci krawedzi) 
		//zapisywac miasta po ktorych idziemy
		
		//foundTrips - wszytskie wierzcholki grafu
		//quest[i].town1 - wierzcholek poczatkowy
	}
	
	//MyList<trip> foundTrips;
	MyList<coordinates> visited;
	cout << "searching";
	//szukanie wszytskich polaczen
	search(cities.valueAt(0), { cities.valueAt(0).pozX, cities.valueAt(0).pozY }, visited, trips, map);

	cout << trips;
	//cout << foundTrips;

	// search for trips
	/*for (int i = 0; i < cities.size(); i++) {
		city c = cities.valueAt(i);
		MyList<coordinates> visited;
		MyList<coordinatesWithCounter> queue;
		queue.add({ c.pozX, c.pozY });
		while (queue.size() > 0) {
			coordinates current = queue.valueAt(0);
			queue.deleteAt(0);

			if (isOnMap(current.x, current.y - 1)) {
				char character = map[current.x][current.y - 1];
				if (visited.find({ current.x, current.y - 1 }) == nullptr) {
					visited.add({ current.x, current.y - 1 });

					if (character == '#') {
						queue.add({ current.x, current.y - 1 });
					}
					else if (character == '*') {

					}
				}
			}
			if (isOnMap(current.x, current.y + 1)) {
				map[current.x][current.y + 1];

			}
			if (isOnMap(current.x - 1, current.y)) {
				map[current.x - 1][current.y];

			}
			if (isOnMap(current.x + 1, current.y)) {
				map[current.x + 1][current.y];
			}
		}
	}*/

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