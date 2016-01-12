#pragma once
#include <string>
#include "map.h"

using namespace std;

class enemies
{
public:
	enemies();
	void enemies::addEnemy(map* pTheMap, string type, int x, int y);
	void enemies::removeEnemy(map* pTheMap, string type, int x, int y);
	void enemies::moveEnemy(map* pTheMap, string type, int x, int y);
	bool enemies::isEnemy(map* pTheMap, int x, int y);
private:
	void enemies::randomMove(map* pTheMap, string type, int x, int y);

	int directionChoice;
	bool hasMoved;
	vector<int> moveTo;
	bool isKilled;
};

