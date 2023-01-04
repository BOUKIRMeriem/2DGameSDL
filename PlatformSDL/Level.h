#pragma once
#include <vector>
#include <iostream>
#include "Key.h"

#include "Wall.h"
#include "Player.h"
#include "Background.h"

class Level {

public:
	GameObject* player;
	vector<GameObject*> objects;

	Level() {
		
	}


};