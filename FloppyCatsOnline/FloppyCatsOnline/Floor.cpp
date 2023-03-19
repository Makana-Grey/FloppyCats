#include "Game.hpp"
#include "Floor.hpp"
#include "definitions.hpp"
#include <stdlib.h>

Floor::Floor() {
	float factor = Game::height / FLOOR_SIDE_PART / FLOOR_HEIGHT;
	width_ = FLOOR_WIDTH * factor;
	collider_y_ = Game::height - FLOOR_HEIGHT * factor;

	unsigned count = Game::width / width_ + 2;
	IntRect rect(
		FLOOR_X + FLOOR_WIDTH * (rand() % FLOOR_COUNT),
		FLOOR_Y, FLOOR_WIDTH, FLOOR_HEIGHT
	);

	while (count--) {
		Sprite* sp = new Sprite(Game::getSpriteList());
		sp->setTextureRect(rect);
		sp->setScale(factor, factor);
		sp->setPosition(count * width_ - 1, collider_y_);
		sprites_.push_back(sp);
	}

	speed_ = Game::width / FLOOR_SPEED_PART;
}

const float& Floor::getCollider() {
	return collider_y_;
}

void Floor::update() {
	float offset = speed_ * Game::deltaTime;

	for (auto sprite : sprites_) {
		sprite->setPosition(sprite->getPosition().x - offset, sprite->getPosition().y);
	}
};

void Floor::fixedUpdate() {
	for (unsigned i = 0; i < sprites_.size(); i++) {
		if (sprites_[i]->getPosition().x < -1 * width_ * 1.1f) {
			float max_x = sprites_[i]->getPosition().x;

			for (auto sprite : sprites_) {
				if (sprite->getPosition().x > max_x) {
					max_x = sprite->getPosition().x;
				}
			}

			sprites_[i]->setPosition(max_x + width_, sprites_[i]->getPosition().y);
			return;
		}
	}
};

void Floor::draw(RenderTarget& target, RenderStates states) const {
	for (auto sprite : sprites_) {
		target.draw(*sprite, states);
	}
}