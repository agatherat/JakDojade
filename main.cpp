#include <iostream>
//#include <MyString>
#include <fstream>
#include "List.h"
#include "MyString.h"
#define MAXINT  2147483647
//#include "MyString.h"
using namespace std;

struct city {
	MyString name;
	int pozX;
	int pozY;
};

struct trip {
	MyString start;
	MyString destination;
	int time;
};

struct question {
	MyString town1;
	MyString town2;
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

struct coordinatesWithCounter {
	int counter;
	coordinates coordinates;
};

int height;
int width;
MyList <city> cities;
MyList <trip> trips;

bool isOnMap(int x, int y) {
	if (x >= 0 && y >= 0 && y < height && x < width) {
		return true;
	}
	else return false;
}

bool findLetter(int x, int y, char** map) {
	//if(map[x][y] != '*' && map[x][y] != '.' && map[x][y] != '#'){
	if (isOnMap(x, y)) {
        char letter = map[y][x];
		if ((letter >= '0' && letter <= '9') || (letter >= 'A' && letter <= 'Z')) {
			return true;
		}
		else return false;
	}
	return false;
}

MyString findCityName(int x, int y, char** map) {
	//mamy jakas litere na miejscu x y
	MyString tmp;
	//char litera;
	int x1=x;
	
	//szukamy poczatku wyrazu
	//koniec mapy?
	//if (x1 != 0&&map[x1 - 1][y] != '*' && map[x1 - 1][y] != '.' && map[x1 - 1][y] != '#') {

	while(findLetter(x1 - 1, y, map)) {
		x1--;
	}

	for (int i = x1; i < x; i++) {
		tmp = tmp + map[y][i];
	}
	x1 = x;
	//koniec wyrazu
	//konec mapy????
	while (findLetter(x1 + 1, y, map)) {
		x1++;
	}
	
	for (int i = x; i <= x1; i++) {
		tmp = tmp+ map[y][i];
	}
	
	return tmp;
}


void search(city firstCity, coordinates current, MyList<coordinates> visited, MyList<trip>& trips, char** map, int distance = 1) {
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
			char character = map[newCoords.y][newCoords.x];
			if (visited.find(newCoords) == nullptr) { //czemu sprawdzamy czy nullptr???
				visited.add(newCoords); //dodajemy koordynaty do odwiedzonych

				if (character == '#') {
					search(firstCity, newCoords, visited, trips, map, distance + 1);
				}
				else if (character == '*') { //znalezlismy miasto
					trip t; 
					t.start = firstCity.name;
					for (int i = 0; i < cities.size(); i++) {
						city c = cities.valueAt(i);
						if (c.pozX == newCoords.x && c.pozY == newCoords.y) {
							t.destination = c.name;
							break;
						}
					}
					t.time = distance;
					trips.add(t); //dodajemy do trips
				}
			}
		}
	}
}

void bfs(city firstCity, coordinates firstCoords, MyList<trip>& trips, char** map) {
	MyList<coordinates> visited;
	MyList<coordinatesWithCounter> Q;
	Q.add({1, firstCoords });
	visited.add(firstCoords);
	while (Q.size() > 0) {
		coordinatesWithCounter newCurrent = Q.valueAt(0);
		Q.deleteAt(0);

		char character = map[newCurrent.coordinates.y][newCurrent.coordinates.x];
		
		coordinates coordinatesToCheck[] = {
			{newCurrent.coordinates.x, newCurrent.coordinates.y - 1},
			{newCurrent.coordinates.x, newCurrent.coordinates.y + 1},
			{newCurrent.coordinates.x - 1, newCurrent.coordinates.y},
			{newCurrent.coordinates.x + 1, newCurrent.coordinates.y}
		};

		for (int j = 0; j < 4; j++) {
			coordinates newCoords = coordinatesToCheck[j];
			if (isOnMap(newCoords.x, newCoords.y)) {
				char character = map[newCoords.y][newCoords.x];
				if (character == '#' && visited.find(newCoords) == nullptr) { //czemu sprawdzamy czy nullptr???
					visited.add(newCoords); //dodajemy koordynaty do odwiedzonych
					Q.add({ newCurrent.counter + 1, newCoords });
				}
				else if (character == '*') { //znalezlismy miasto
					trip t;
					t.start = firstCity.name;
					for (int i = 0; i < cities.size(); i++) {
						city c = cities.valueAt(i);
						if (c.pozX == newCoords.x && c.pozY == newCoords.y) {
							t.destination = c.name;
							break;
						}
					}
					t.time = newCurrent.counter;
					trips.add(t); //dodajemy do trips
				}
			}
		}
	}
}

// https://eduinf.waw.pl/inf/alg/001_search/0138.php
void x(question q) {
	MyList<MyString> cityNames;
	for (int i = 0; i < cities.size(); i++) {
		cityNames.add(cities.valueAt(i).name);
	}

	/*MyList<MyString> S;
	MyList<MyString> Q;
	for (int i = 0; i < cities.size(); i++) {
		Q.add(cities.valueAt(i).name);
	}*/
	MyList<int> S;
	MyList<int> Q;
	for (int i = 0; i < cities.size(); i++) {
		Q.add(i);
	}

	int* d = new int[cities.size()];
	int* p = new int[cities.size()];
	for (int i = 0; i < cities.size(); i++) {
		d[i] = MAXINT;
	}
	//cityNames.findindex(q.town1);

	int firstCityIndex = cityNames.findindex(q.town1);

	d[firstCityIndex] = 0;

	for (int i = 0; i < cities.size(); i++) {
		p[i] = -1;
	}

	// K08
	while (Q.size() > 0) {
		int min = d[Q.valueAt(0)];
		int minIndex = Q.valueAt(0);
		for (int i = 1; i < Q.size(); i++) {
			int cityIndex = Q.valueAt(i);
			if (d[cityIndex] < min) {
				min = d[cityIndex];
				minIndex = cityIndex;
			}
		}

		// K09
		/*cout << "-----------------";
		cout << S << endl;
		cout << Q << endl;*/

		S.add(minIndex);
		int indexToDelete = Q.findindex(minIndex);
		//cout << indexToDelete << endl;

		Q.deleteAt(indexToDelete);

		/*cout << S << endl;
		cout << Q << endl;
		cout << "-----------------";*/


		// K10
		MyString currentCityName = cityNames.valueAt(minIndex);
		//MyList<int> neighbours;
		Node<trip>* tmp = trips.head;
		//int tripsSize = trips.size();
		while (tmp != nullptr) {
			trip currentTrip = tmp->value;

			tmp = tmp->next;
		/*}

		for (int i = 0; i < trips.size(); i++) {
			trip currentTrip = trips.valueAt(i);*/
			if (currentTrip.start == currentCityName) {
				MyString neighbourName = currentTrip.destination;
				int neighbourIndex = cityNames.findindex(neighbourName);
				if (Q.find(neighbourIndex) == nullptr) {
					continue;
				}
				if (d[neighbourIndex] > d[minIndex] + currentTrip.time) {
					d[neighbourIndex] = d[minIndex] + currentTrip.time;
					p[neighbourIndex] = minIndex;
				}
			}
		}
	}
	/*for (int i = 0; i < cities.size(); i++) {
		cout << d[i] << ' ';
	}
	cout << endl;
	for (int i = 0; i < cities.size(); i++) {
		cout << cityNames.valueAt(p[i]) << ' ';
	}
	cout << endl;*/
//	cout << "CIty names: ";
//	cout << cityNames << endl;
//	for (int i = 0; i < cities.size(); i++) {
//		cout << d[i] << ' ';
//	}
//	cout << endl;
//
//	for (int i = 0; i < cities.size(); i++) {
//		cout << p[i] << ' ';
//	}
//	cout << endl;


	int destIndex = cityNames.findindex(q.town2);
	cout << d[destIndex] << ' ';

	MyList<MyString> cityPath;

	if (destIndex != firstCityIndex) {
		int previousIndex = p[destIndex];
		while (previousIndex != firstCityIndex) {
			cityPath.add(cityNames.valueAt(previousIndex));
			previousIndex = p[previousIndex];
		}
	}
	
	
	if (q.type == 1) {
		for (int i = cityPath.size() - 1; i >= 0; i--) {
			cout << cityPath.valueAt(i) << ' ';
		}
	}
	cout << endl;
}

int main() {
	int flightCounter; //liczba polaczen lotniczych
	int questCounter; //liczba zapytan

	cin >> width;
	cin >> height;

	char** map = new char* [height];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width];
	}
	
	// wczytanie wartoœci do tablicy
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cin >> map[i][j];
		}
	}

//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			cout << map[i][j];
//		}
//		cout << endl;
//	}

	cin >> flightCounter;
	/*char znak; 
	znak = getchar();*/
	for (int i = 0; i < flightCounter; i++) {
		trip plane;

		cin >> plane.start;
		cin >> plane.destination;
		cin >> plane.time;

		trips.add(plane); // dodajemy lot do listy mozliwych przejazdow 
	}


	cin >> questCounter;
	MyList<question> quests;
	for (int i = 0; i < questCounter; i++) {
		question quest;

		cin >> quest.town1;
		cin >> quest.town2;
		cin >> quest.type;
		quests.add(quest); 
	}

	//question* quest = new question[questCounter];
	//for (int i = 0; i < questCounter; i++) {
	//	cin >> quest[i].town1;
	//	cin >> quest[i].town2;
	//	cin >> quest[i].type;
	//}

	//zapisywanie miast do listy
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//szukanie gwiazdki z kazdej strony 
			if (map[i][j] == '*') {
				city c;
				c.pozX = j;
				c.pozY = i;

				if (findLetter(j - 1, i, map)) { c.name = findCityName(j - 1, i, map); }
				else if (findLetter(j + 1, i, map)) { c.name = findCityName(j + 1, i, map); }
				else if (findLetter(j, i - 1, map)) { c.name = findCityName(j, i - 1, map); }
				else if (findLetter(j, i + 1, map)) { c.name = findCityName(j, i + 1, map); }
				else if (findLetter(j + 1, i + 1, map)) { c.name = findCityName(j + 1, i + 1, map); }
				else if (findLetter(j - 1, i - 1, map)) { c.name = findCityName(j - 1, i - 1, map); }
				else if (findLetter(j + 1, i - 1, map)) { c.name = findCityName(j + 1, i - 1, map); }
				else if (findLetter(j - 1, i + 1, map)) { c.name = findCityName(j - 1, i + 1, map); }
				else throw;

				cities.add(c); //dodanie miasta do tablicy
			}
		}
	}
	
	//szukanie najkrotszej drogi
	for (int i = 0; i < cities.size(); i++) {
		bfs(cities.valueAt(i), { cities.valueAt(i).pozX, cities.valueAt(i).pozY }, trips, map);
		//MyList<coordinates> visited;
		//search(cities.valueAt(i), { cities.valueAt(i).pozX, cities.valueAt(i).pozY }, visited, trips, map);
	}
	
	//szukanie wszytskich polaczen
	//search(cities.valueAt(0), { cities.valueAt(0).pozX, cities.valueAt(0).pozY }, visited, trips, map);

	//cout << trips << endl;
	/*cout << "znalezione" << endl;
	cout << quest[0].town1 << endl;
	cout << quest[0].town2 << endl;
	cout << trips;*/
	for (int i = 0; i < questCounter; i++) {
		question q = quests.valueAt(i);
		x(q);
		///x(quest[i]);
	}
	//cout << trips << endl;
	
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