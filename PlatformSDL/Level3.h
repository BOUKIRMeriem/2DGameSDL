#pragma once
#include "Level.h"
class Level3 : public Level {

public:

	Level3() {
		objects.clear();
		player = new Player(200, 550, 4);

		// add all objects to linked list
		objects.push_back(new Background());
		// 
		// add player
		objects.push_back(player);

		// add wall
		objects.push_back(new Wall(0, 650, 600, 100));
		objects.push_back(new Wall(100, 560, 40, 40));
		objects.push_back(new Wall(0, 480, 40, 40));
		objects.push_back(new Wall(150, 380, 40, 40));
		objects.push_back(new Wall(210, 240, 400, 40));

		objects.push_back(new Wall(510, 340, 200, 40, 4000)); // moving wall

		objects.push_back(new Wall(1010, 240, 400, 40));


		// add key
		objects.push_back(new Key(1200, 200));

	}
};