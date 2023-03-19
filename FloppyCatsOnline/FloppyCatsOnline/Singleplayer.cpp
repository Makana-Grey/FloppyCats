#include "Game.hpp"
#include "Singleplayer.hpp"
#include "definitions.hpp"
#include <string>

Singleplayer::Singleplayer() {
	gameObjects.push_back(obstacle);
	gameObjects.push_back(floor);
	gameObjects.push_back(player);

	text_ = new TextObject(std::to_string(score_), Vector2f(50, 50), 2.f, Color(0xff00ffff));
	gameObjects.push_back(text_);
}

void Singleplayer::update() {
	defineCollisions(*player);
	definePassObstacle(*player);
	Scene::update();
}

void Singleplayer::fixedUpdate() {
	if (action_duration > GAMEPLAY_ACTION_DURATION) {
		if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Up)) {
			if (player->getState() != Dead) {
				if (!is_over) {
					player->jump();
					obstacle->setIsMove(true);
				}
				else if (is_over) {
					is_reset_ = true;
				}
			}
		}
	}
	action_duration += Game::fixedDeltaTime;

	Scene::fixedUpdate();
}

void Singleplayer::freeWindow() {
	if (is_reset_) {
		delete player;
		delete obstacle;
		delete floor;
		gameObjects.clear();

		initObjects();
		gameObjects.push_back(obstacle);
		gameObjects.push_back(floor);
		gameObjects.push_back(player);
		player->jump();

		gameObjects.push_back(text_);
		score_ = 0;
		text_->setText(std::to_string(score_));

		is_over = is_reset_ = false;
	}
}

void Singleplayer::onCollideWithObstacle() {
	player->dead();
	obstacle->setIsMove(false);
}

void  Singleplayer::onCollideWithFloor() {
	if (player->getState() != Dead) {
		player->dead();
		obstacle->setIsMove(false);
	}
	is_over = true;
	player->setIsAnimate(false);
	player->wait();
}

void Singleplayer::onPassObstacle() {
	text_->setText(std::to_string(++score_));
	obstacle->setYPosition(obstacle->generateYPosition());
}
