#include "map.h"
#include <vector>
#include <iostream>

using namespace std;


map::map(){
}

void map::blankRoom(int level) {
	//increase as the levels go up
	height = 7 + (level / 2);
	width = 7 + (level / 2);

	//Get y setup
	theMap.resize(height);

	for (int i = 0; i < height; i++) {
		//get x setup
		theMap[i].resize(width);

		//populate to empty
		for (int a = 0; a != width; a++) {
			theMap[i][a] = ' ';
		}
	}
}

void map::insertElement(char element, int x, int y) {
	theMap[x][y] = element;
}

char map::getElement(int x, int y) {
	return theMap[x][y];
}

bool map::isEmpty(int x, int y) {
	if (theMap[x][y] == ' ') {
		return true;
	}
	else {
		return false;
	}
}

int map::getMax() {
	return height - 1;
}

void map::drawMap() {
	system("CLS");

	cout << "-";
	for (int x = 0; x < width; x++) {
		cout << "---";
	}
	cout << "-" << endl;

	for (int y = 0; y < height; y++) {
		cout << "-";
		for (int x = 0; x < width; x++) {
			cout << "|" << theMap[y][x] << "|";
		}
		cout << "|" << endl;
	}
	cout << "-";
	for (int x = 0; x < width; x++) {
		cout << "---";
	}
	cout << "-" << endl;
}

