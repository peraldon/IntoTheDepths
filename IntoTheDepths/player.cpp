#include "player.h"
#include "item.h"
#include <vector>
#include <iostream>

using namespace std;

player::player(){
	playerLocation.resize(2);
	dead = false;
	playerItem = "NONE";
}

vector<int> player::getPlayerLocation() {
	return playerLocation;
}

int player::getPlayerX() {
	return playerLocation[0];
}
int player::getPlayerY() {
	return playerLocation[1];
}

void player::setPlayerLocation(int x, int y) {
	playerLocation[0] = x;
	playerLocation[1] = y;
}

//Returns false if the move is not legal, and true if the move is legal and made
bool player::playerMove(map* pTheMap, enemies* pTheEnemies, item* pTheItems, char input) {
	newPlayerLocation = playerLocation;

	//create new player move attempt
	if (input == 'w') {
		newPlayerLocation[0]--;
	}
	else if (input == 'a') {
		newPlayerLocation[1]--;
	}
	else if (input == 's') {
		newPlayerLocation[0]++;
	}
	else { //playerInput == d
		newPlayerLocation[1]++;
	}

	//out of bounds check
	if (newPlayerLocation[0] <= pTheMap->getMax() && newPlayerLocation[0] >= 0 && newPlayerLocation[1] <= pTheMap->getMax() && newPlayerLocation[1] >= 0) {
		
		//enemy check
		if (pTheEnemies->isEnemy(pTheMap, newPlayerLocation[0], newPlayerLocation[1])) {
			playerDeath();
			return true;
		}
		else {
			//items
			if (pTheMap->getElement(newPlayerLocation[0], newPlayerLocation[1]) == '*') {
				playerItem = pTheItems->generateItem();
			}
			//move success
			pTheMap->insertElement(' ', playerLocation[0], playerLocation[1]);
			pTheMap->insertElement('P', newPlayerLocation[0], newPlayerLocation[1]);
			playerLocation = newPlayerLocation;
			return true;
		}


	}
	else {
		//bounds check failed
		return false;
	}
}

void player::playerDeath() {
	system("CLS");

	cout << "-";
	for (int x = 0; x < 20; x++) {
		cout << "---";
	}
	cout << "-" << endl;

	for (int y = 0; y < 20; y++) {
		cout << "-";
		for (int x = 0; x < 20; x++) {
			cout << "|" << "x" << "|";
		}
		cout << "|" << endl;
	}
	cout << "-";
	for (int x = 0; x < 20; x++) {
		cout << "---";
	}
	cout << "-" << endl;

	dead = true;
}

bool player::isDead() {
	return dead;
}

string player::getItem() {
	return playerItem;
}

void player::removeItem() {
	playerItem = "NONE";
}