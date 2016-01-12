#include <iostream>
#include <vector>
#include <conio.h>
#include "map.h"
#include "player.h"
#include "enemies.h"
#include "item.h"

using namespace std;


bool isPlaying;
int level;

map theMap = map();
player thePlayer = player();
enemies theEnemies = enemies();
item theItems = item();

char moveInput;
bool hasMoved; 

//pointers to access the main instances
map* pTheMap = &theMap;
player* pThePlayer = &thePlayer;
enemies* pTheEnemies = &theEnemies;
item* pTheItems = &theItems;

vector<string> helpText = { 
	"P - This is you! Move using the WASD keys.", 
	"X - This is the exit to the next level! Land on it to finish the room.",
	"$ - This is an item you can pickup! They're needed to be able to get far.",
	"t - This is a trap! They don't move, but you'll die if you land on one.", 
	"m - This is a basic grunt. They just wander around the place randomly." };
size_t scrollNumber;
bool isHelp;

//the help menu
void help() {
	scrollNumber = 0;
	isHelp = true;

	system("CLS");
	cout << "     THE LEGEND" << endl << "---------------------" << endl << "- Navigate the legend with the 'w' and 's' keys.\n- Get back to the game with the 'h' key." << endl << "---------------------" << endl;
	cout << helpText[0] << endl << helpText[1] << endl << helpText[2] << endl;
	cout << "---------------------" << endl;

	while (isHelp) {
		moveInput = _getch();

		if (moveInput == 'h') {
			isHelp = false;
			continue;
		}
		else if (moveInput == 'w') {
			if (scrollNumber != 0) {
				scrollNumber--;
			}
		}
		else if (moveInput == 's') {
			if (scrollNumber < helpText.size()-3) {
				scrollNumber++;
			}
		}

		system("CLS"); 
		cout << "     THE LEGEND" << endl << "---------------------" << endl << "- Navigate the legend with the 'w' and 's' keys.\n- Get back to the game with the 'h' key." << endl << "---------------------" << endl;
		cout << helpText[scrollNumber] << endl << helpText[scrollNumber+1] << endl << helpText[scrollNumber+2] << endl;
		cout << "---------------------" << endl;
	}


}

//return true if the player has reached 'x'
bool victoryCheck() {
	if (thePlayer.getPlayerX() == theMap.getMax() && thePlayer.getPlayerY() == theMap.getMax()){
		level++;
		return true;
	}
	else {
		return false;
	}
}

//wipe the room, expand it if needed, and reset locations
void newRoom() {
	int x, y;

	//the dungeon has a max size of 20
	if (level > 20) {
		theMap.blankRoom(20);
	}
	else {
		theMap.blankRoom(level);
	}

	//setup player
	theMap.insertElement('P', 0, 0);
	thePlayer.setPlayerLocation(0, 0);
	//setup exit
	theMap.insertElement('X', theMap.getMax(), theMap.getMax());

	//setup NORMAL_TRAPS
	for (int i = 0; i != level; i++) {
	x = rand() % theMap.getMax();
	y = rand() % theMap.getMax();

	while (theMap.getElement(x, y) != ' ') {
	x = rand() % theMap.getMax();;
	y = rand() % theMap.getMax();;
	}
	theEnemies.addEnemy(pTheMap, "NORMAL_TRAP", x, y);
	}

	//setup GRUNTS
	for (int i = 0; i != level / 2; i++) {
	x = rand() % theMap.getMax();
	y = rand() % theMap.getMax();

	while (theMap.getElement(x, y) != ' ') {
	x = rand() % theMap.getMax();
	y = rand() % theMap.getMax();
	}
	theEnemies.addEnemy(pTheMap, "GRUNT", x, y);
	}

	//setup ITEM
	if (int r = rand() % 10 + 1 == 1) {
		x = rand() % theMap.getMax();
		y = rand() % theMap.getMax();

		while (theMap.getElement(x, y) != ' ') {
			x = rand() % theMap.getMax();
			y = rand() % theMap.getMax();
		}
		theMap.insertElement('*', x, y);
	}
}
	

//the main game loop
void gameLoop() {
	hasMoved = false;

	//draw screen
	theMap.drawMap();
	cout << "Level: " << level << " - 'h' for help " << endl;
	
	if (thePlayer.getItem() != "NONE") {
		cout << "Type 'f' to use '" << thePlayer.getItem() << "'." << endl;
	}


	//player turn
	while (!hasMoved) {
		moveInput = _getch();
		//player move
		if (moveInput == 'w' || moveInput == 'a' || moveInput == 's' || moveInput == 'd') {
			hasMoved = thePlayer.playerMove(pTheMap, pTheEnemies, pTheItems, moveInput);
		}
		else if (moveInput == 'h') {
			help();
			//redraw screen
			theMap.drawMap();
			cout << "Level: " << level << endl;
		}
		else if (moveInput == 'f') {
			//use item
			theItems.useItem(pTheMap, thePlayer.getPlayerLocation(), thePlayer.getItem());
			thePlayer.removeItem();
			//redraw screen without the 'type f to use' etc
			theMap.drawMap();
			cout << "Level: " << level << " - 'h' for help " << endl;
		}
	}
	//death check
	if (thePlayer.isDead()) {
		isPlaying = false;
	}
	// victory check
	if (victoryCheck()) {
		newRoom();
		return;
	}

	//enemies act
	for (int x = 0; x < theMap.getMax(); x++) {
		for (int y = 0; y != theMap.getMax(); y++) {
			if (theEnemies.isEnemy(pTheMap, x, y)) {
				if (theMap.getElement(x, y) == 'm') {
					theEnemies.moveEnemy(pTheMap, "GRUNT", x, y);
				}
			}
		}
	}

	//Change new enemy placements to valid enemy placements
	for (int i = 0; i < theMap.getMax(); i++) {
		for (int a = 0; a < theMap.getMax(); a++) {
			if (theMap.getElement(i, a) == 'n') {
				theMap.insertElement('m', i, a);
			}
		}
	}

		// - victory check
}

void setup() {

	cout << "--------------------" << endl << " - Into The Depths - " << endl << "--------------------" << endl;
	cout << "Use the WASD keys to move." << endl << "Once you're ready to start playing, hit any button" << endl;

	char temp = _getch();
	
	newRoom();
	isPlaying = true;
}

int main(){

	setup();

	while (isPlaying) {
		gameLoop();
	}

	cout << "You lost the game, sorry!" << endl << "You managed to reach level " << level << "." << endl;
	system("pause");
	return 0;
}
