#pragma once
#include <vector>

using namespace std;

class map
{
public:
	map();
	void map::blankRoom(int level);
	void map::insertElement(char element, int x, int y);
	char map::getElement(int x, int y);
	bool map::isEmpty(int x, int y);
	int map::getMax();
	void map::drawMap();
private:
	vector<vector<char>> theMap;
	int height;
	int width;
};

