#pragma once
#include "Level.h"
class Level1 : public Level{

public:

	Level1() {
		objects.clear();
		player = new Player(100, 400, 4);

		// add all objects to linked list
		objects.push_back(new Background());

		//add player
		objects.push_back(player);

		// add wall
		objects.push_back(new Wall(0,650,600,100));
		objects.push_back(new Wall(700, 650, 700, 100));
		objects.push_back(new Wall(0, 0, 30, 800));
		objects.push_back(new Wall(1300, 0, 30, 800));

		// add key
		objects.push_back(new Key(1000,600));

	}
};