#pragma once
#include "Level.h"
class Level2 : public Level {

public:

	Level2() {
		objects.clear();
		player = new Player(200, 550, 4);

		// add all objects to linked list
		objects.push_back(new Background());

		objects.push_back(player); // add player to list of object

		// add walls
		objects.push_back(new Wall(0, 650, 600, 100));
		objects.push_back(new Wall(100, 560, 40, 40));
		objects.push_back(new Wall(0, 480, 40, 40));
		objects.push_back(new Wall(150, 400, 40, 40));
		objects.push_back(new Wall(300, 350, 40, 40));
		objects.push_back(new Wall(110, 240, 40, 40));

		// add the key
		objects.push_back(new Key(30, 100));

	}
};