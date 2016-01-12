#pragma once
#include <vector>
#include <string>
#include "map.h"
#include "enemies.h"
#include "item.h"

using namespace std;

class player
{
public:
	player();
	vector<int> player::getPlayerLocation();
	int player::getPlayerX();
	int player::getPlayerY();
	void player::setPlayerLocation(int x, int y);

	bool player::playerMove(map* pTheMap, enemies* pTheEnemies, item* pTheItems, char input);

	string player::getItem();
	void player::removeItem();

	void player::playerDeath();
	bool player::isDead();
private:
	vector<int> playerLocation;
	vector<int> newPlayerLocation;
	bool dead;
	string playerItem;

};

