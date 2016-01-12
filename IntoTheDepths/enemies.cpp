#include "enemies.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;


enemies::enemies(){
}

void enemies::addEnemy(map* pTheMap, string type, int x, int y) {	
	//types of monster
	if (type == "NORMAL_TRAP") {
		pTheMap->insertElement('t', x, y);
	}
	else if (type == "GRUNT") {
		pTheMap->insertElement('m', x, y);
	}
	else if (type == "STALKER") {
		pTheMap->insertElement('M', x, y);
	}
}

void enemies::removeEnemy(map* pTheMap, string type, int x, int y) {
		pTheMap->insertElement(' ', x, y);

}

void enemies::moveEnemy(map* pTheMap, vector<int> playerLocation, string type, int x, int y) {
	vector<int> location = { x, y };

	if (type == "GRUNT") {
		randomMove(pTheMap, type, x, y);
	}
	if (type == "STALKER") {
		//Will move towards the player if it can see them.
		if (canSee(location, playerLocation, 2)) {
			attackMove(pTheMap, playerLocation, type, x, y);
		}
		else {
			randomMove(pTheMap, type, x, y);
		}
	}
}

void enemies::randomMove(map* pTheMap, string type, int x, int y) {
	directionChoice = NULL;
	moveTo.resize(2);
	isKilled = false;
	hasMoved = false;


	while (!hasMoved) {
		directionChoice = rand() % 4 + 1;
		moveTo[0] = x;
		moveTo[1] = y;
		if (directionChoice == 1) {
			//up
			moveTo[0]--;
		}
		else if (directionChoice == 2) {
			//left
			moveTo[1]--;
		}
		else if (directionChoice == 3) {
				//down
				moveTo[0]++;
		}
		else { //right
				moveTo[1]++;
		}

		//out of bounds check
		if (moveTo[0] < pTheMap->getMax() && moveTo[1] < pTheMap->getMax() && moveTo[0] > -1 && moveTo[1] > -1) {
			if (pTheMap->getElement(moveTo[0], moveTo[1]) == ' ') {
					//move succeed
					pTheMap->insertElement(' ', x, y); //empty previous slot
					pTheMap->insertElement(getIconNew(type), moveTo[0], moveTo[1]); //fill new slot

					hasMoved = true;
					directionChoice = NULL;
					break;
			}
			else if (pTheMap->getElement(moveTo[0], moveTo[1]) == 'P') {
				isKilled = true;
				break;
			}
		}
	}
}
void enemies::attackMove(map* pTheMap, vector<int> playerLocation, string type, int x, int y) {

	if (playerLocation[0] >= x) {
		directionChoice = 4;
	}
	else if (playerLocation[1] >= y) {
		directionChoice = 1;
	}
	else if (playerLocation[0] <= x) {
		directionChoice = 2;
	}
	else if (playerLocation[1] <= y) {
		directionChoice = 3;
	}
	else {
		directionChoice = 1;
	}

	moveTo.resize(2);
	isKilled = false;
	hasMoved = false;

	moveTo[0] = x;
	moveTo[1] = y;
	if (directionChoice == 1) {
		//up
		moveTo[0]--;
	}
	else if (directionChoice == 2) {
		//left
		moveTo[1]--;
	}
	else if (directionChoice == 3) {
		//down
		moveTo[0]++;
	}
	else { //right
		moveTo[1]++;
	}

	//out of bounds check
	if (moveTo[0] < pTheMap->getMax() && moveTo[1] < pTheMap->getMax() && moveTo[0] > -1 && moveTo[1] > -1) {
		if (pTheMap->getElement(moveTo[0], moveTo[1]) == ' ') {
			//move succeed
			pTheMap->insertElement(' ', x, y); //empty previous slot
			pTheMap->insertElement(getIconNew(type), moveTo[0], moveTo[1]); //fill new slot

			hasMoved = true;
			directionChoice = NULL;
		}
		else if (pTheMap->getElement(moveTo[0], moveTo[1]) == 'P') {
			isKilled = true;
		}
	}
}

bool enemies::isEnemy(map* pTheMap, int x, int y) {
	if (pTheMap->getElement(x, y) =='m' || pTheMap->getElement(x, y) == 't' || pTheMap->getElement(x, y) == 'M') {
		return true;
	}
	else {
		return false;
	}
}
char enemies::getIcon(string type) {
	//setup icon
	if (type == "GRUNT") {
		return 'm';
	}
	else if (type == "STALKER") {
		return 'M';
	}
}
char enemies::getIconNew(string type) {
	//setup icon
	if (type == "GRUNT") {
		return 'n';
	}
	else if (type == "STALKER") {
		return 'N';
	}
}

bool enemies::canSee(vector<int> searcher, vector<int> object, int range) {
	//takes the smallest from the biggest
	if ((searcher[0] > object[0] ? searcher[0] - object[0] : object[0] - searcher[0]) <= range && (searcher[1] > object[1] ? searcher[1] - object[1] : object[1] - searcher[1]) <= range) {
		return true;
	}
	else {
		return false;
	}
}