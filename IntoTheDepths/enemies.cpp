#include "enemies.h"
#include <string>
#include <iostream>

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
}

void enemies::removeEnemy(map* pTheMap, string type, int x, int y) {
		pTheMap->insertElement(' ', x, y);

}

void enemies::moveEnemy(map* pTheMap, string type, int x, int y) {

	if (type == "GRUNT") {
		randomMove(pTheMap, type, x, y);
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
					pTheMap->insertElement('n', moveTo[0], moveTo[1]); //fill new slot

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

bool enemies::isEnemy(map* pTheMap, int x, int y) {
	if (pTheMap->getElement(x, y) =='m' || pTheMap->getElement(x, y) == 't') {
		return true;
	}
	else {
		return false;
	}
}