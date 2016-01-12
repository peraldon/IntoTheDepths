#include <string>

#include "item.h"
#include "map.h"

using namespace std;

item::item(){
	itemList = {"Iron Sword", "Trap Bypasser"};
}

void item::useItem(map* pTheMap, vector<int> playerLocation, string item) {
	if (item == "Iron Sword") {
		//Does a check at all 4 slots around the player. Kills monsters there if there is one. Starts top, goes clockwise
		if (playerLocation[1] > 0 && pTheMap->getElement(playerLocation[0], playerLocation[1] - 1 == 'm')) {
			pTheMap->insertElement(' ', playerLocation[0], playerLocation[1] - 1);
		}
		if (playerLocation[0] < pTheMap->getMax() && pTheMap->getElement(playerLocation[0] + 1, playerLocation[1] == 'm')) {
			pTheMap->insertElement(' ', playerLocation[0] + 1, playerLocation[1]);
		}
		if (playerLocation[1] < pTheMap->getMax() && pTheMap->getElement(playerLocation[0], playerLocation[1] + 1 == 'm')) {
			pTheMap->insertElement(' ', playerLocation[0], playerLocation[1] + 1);
		}
		if (playerLocation[0] > 0 && pTheMap->getElement(playerLocation[0] - 1, playerLocation[1] == 'm')) {
			pTheMap->insertElement(' ', playerLocation[0] - 1, playerLocation[1]);
		}
	}
	else if (item == "Trap Bypasser") {
		//Does a check at all 4 slots around the player. Kills traps there if there is one. Starts top, goes clockwise
		if (playerLocation[1] > 0 && pTheMap->getElement(playerLocation[0], playerLocation[1] - 1 == 't')) {
			pTheMap->insertElement(' ', playerLocation[0], playerLocation[1] - 1);
		}
		if (playerLocation[0] < pTheMap->getMax() && pTheMap->getElement(playerLocation[0] + 1, playerLocation[1] == 't')) {
			pTheMap->insertElement(' ', playerLocation[0] + 1, playerLocation[1]);
		}
		if (playerLocation[1] < pTheMap->getMax() && pTheMap->getElement(playerLocation[0], playerLocation[1] + 1 == 't')) {
			pTheMap->insertElement(' ', playerLocation[0], playerLocation[1] + 1);
		}
		if (playerLocation[0] > 0 && pTheMap->getElement(playerLocation[0] - 1, playerLocation[1] == 't')) {
			pTheMap->insertElement(' ', playerLocation[0] - 1, playerLocation[1]);
		}
	}
}

string item::generateItem() {
	return itemList[rand() % itemList.size()];
}

