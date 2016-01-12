#pragma once
#include <string>
#include <cstdlib>
#include "map.h"

using namespace std;

class enemies
{
public:
	enemies();
	void enemies::addEnemy(map* pTheMap, string type, int x, int y);
	void enemies::removeEnemy(map* pTheMap, string type, int x, int y);

	void enemies::moveEnemy(map* pTheMap, vector<int> playerLocation, string type, int x, int y);

	bool enemies::isEnemy(map* pTheMap, int x, int y);
	char enemies::getIcon(string type);
	char enemies::getIconNew(string type);
private:
	void enemies::randomMove(map* pTheMap, string type, int x, int y);
	void enemies::attackMove(map* pTheMap, vector<int> playerLocation, string type, int x, int y);

	bool enemies::canSee(vector<int> searcher, vector<int> object, int range);

	int directionChoice;
	bool hasMoved;
	vector<int> moveTo;
	bool isKilled;
	char enemyIcon;
	char enemyIconNew;
};

