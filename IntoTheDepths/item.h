#pragma once

#include <string>
#include <vector>

#include "map.h"

using namespace std;

class item
{
public:
	item();

	void item::useItem(map* pTheMap, vector<int> playerLocation, string item);
	string item::generateItem();
private:
	vector<string> itemList;
};

