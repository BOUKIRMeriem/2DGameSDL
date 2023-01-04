#pragma once
#include <vector>
#include <iostream>
#include "Wall.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

using namespace std;

class Game {

	GameObject* player;
	vector<GameObject*> objects;
	vector<Level*> levels;
	int currentLevel = 0;

public:
	Game() {
	}

	void startGame() {

		//printf("p: %f\n", player->getPos().x);
		levels.clear();
		currentLevel = 0;
		levels.push_back(new Level1());
		levels.push_back(new Level2());
		levels.push_back(new Level3());
		
		startLevel(currentLevel); // load current level
	}

	void startLevel(int level) {
		player = levels[currentLevel]->player;
		objects = levels[currentLevel]->objects;
	}

	void update() {

		if (Util::get()->gameStatus == Util::GAMEOVER) { // return if game is gameover screen
			return;
		}
		if (Util::get()->gameStatus == Util::MENU) { // return if game is menu screen
			return;
		}
		checkCollide();


		for (GameObject* obj : objects) {
			obj->update();
		}


		Util::get()->camX = player->getPos().x - 200; // camera follow player

		// check load next level
		if (Util::get()->loadNextLevel ) {
			currentLevel++;
			Util::get()->loadNextLevel = false;

			if (currentLevel > levels.size() - 1) {
				Util::get()->gameStatus = Util::MENU;
				return;
			}

			startLevel(currentLevel);
		}

	}

	void onKeyDown(SDL_Keycode key) {
		if (Util::get()->gameStatus == Util::GAMEOVER) {
			if (key == SDLK_SPACE) { // press space to start the game
				Util::get()->gameStatus = Util::PLAYING;
				startGame();
			}
			return;
		}
		if (Util::get()->gameStatus == Util::MENU) {
			if (key == SDLK_SPACE) { // press space to start the game
				Util::get()->gameStatus = Util::PLAYING;
				startGame();
			}
			return;
		}

		((Player*)player)->onKeyDown(key);
	}
	void onKeyUp(SDL_Keycode key) {
		if (Util::get()->gameStatus == Util::GAMEOVER) {
			return;
		}
		if (Util::get()->gameStatus == Util::MENU) {
			return;
		}
		((Player*)player)->onKeyUp(key);
	}
	void onMouseDown(int x, int y) {
		if (Util::get()->gameStatus == Util::GAMEOVER) {
			return;
		}
		if (Util::get()->gameStatus == Util::MENU) {
			return;
		}
		for (GameObject* obj : objects) {
			obj->onMouseDown(x, y);
		}
	}

	void draw() {
		if (Util::get()->gameStatus == Util::GAMEOVER) {
			Util::get()->showText(200, 100, "Game Over!");
			Util::get()->showText(200, 300, "Pico Park Clone!");
			Util::get()->showText(200, 400, "Press 'Space' to retry!");
			return;
		}
		if (Util::get()->gameStatus == Util::MENU) {
			Util::get()->showText(200, 200, "Pico Park Clone!");
			Util::get()->showText(200, 300, "Press 'Space' to start the game");
			return;
		}

		
		// in game
		for (GameObject* obj : objects) {
			obj->draw();
		}

		Util::get()->showText(10, 10, "WSAD : move", { 32,32,32 });
		Util::get()->showText(10, 30, "Space: jump", { 32,32,32 });
		Util::get()->showText(10, 60, "Goal: Find the Key!", { 255,23,23 });
		Util::get()->showText(10, 90, "Level: " + to_string(currentLevel + 1), {255,233,23});

	}

	void checkCollide() { // check collision for all objects

		for (GameObject* obj : objects) {
			for (GameObject* otherObj : objects) {
				if (obj == otherObj) {
					continue;
				}
				if (obj->checkCollide(otherObj)) { // check collide 
					obj->onCollide(otherObj); // if collide call onCollide
				}
			}
		}
	}
};