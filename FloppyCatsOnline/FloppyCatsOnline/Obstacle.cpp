#include "Obstacle.hpp"
#include "Game.hpp"
#include "definitions.hpp"
#include <algorithm>
#include <stdlib.h>

void Obstacle::generateGap() {
	position_x_ = Game::width;

	sprite_.setPosition(position_x_, position_y_ + gap_height_);
	rect_.setPosition(position_x_, position_y_ + gap_height_ + sprite_height_);

	sprite_reverse_.setPosition(position_x_, position_y_ - sprite_height_);
	rect_reverse_.setPosition(position_x_, position_y_ - sprite_height_);

	collider_.x0 = collider_reverse_.x0 = collider_.x1 = collider_reverse_.x1 = position_x_;
	collider_.x2 = collider_reverse_.x2 = collider_.x3 = collider_reverse_.x3 = position_x_ + sprite_width_;

	collider_.y0 = collider_.y3 = position_y_;
	collider_.y1 = collider_.y2 = position_y_ - rect_reverse_.getSize().y;

	collider_reverse_.y1 = collider_reverse_.y2 = position_y_ + gap_height_;
	collider_reverse_.y0 = collider_reverse_.y3 = rect_.getPosition().y + rect_.getSize().y;
}

Obstacle::Obstacle() {
	sprite_.setTexture(Game::getSpriteList());
	sprite_.setTextureRect(IntRect(OBSTACLE_X, OBSTACLE_Y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT));
	sprite_reverse_.setTexture(Game::getSpriteList());
	sprite_reverse_.setTextureRect(IntRect(OBSTACLE_X, OBSTACLE_Y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT));
	sprite_reverse_.setOrigin(OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
	sprite_reverse_.setRotation(180);

	sprite_width_ = Game::width / OBSTACLE_SIDE_PART / OBSTACLE_WIDTH;

	sprite_.setScale(sprite_width_, sprite_width_);
	sprite_reverse_.setScale(sprite_width_, sprite_width_);

	sprite_height_ = sprite_width_ * OBSTACLE_HEIGHT;
	sprite_width_ *= OBSTACLE_WIDTH;

	rect_.setFillColor(Color(OBSTACLE_COLOR));
	rect_.setSize(Vector2f(sprite_width_, Game::height));
	rect_reverse_.setFillColor(Color(OBSTACLE_COLOR));
	rect_reverse_.setSize(Vector2f(sprite_width_, Game::height));
	rect_reverse_.setOrigin(0, Game::height);

	gap_height_ = Game::height / PLAYER_SIDE_PART * OBSTACLE_GAP_FACTOR;

	speed_ = Game::width / OBSTACLE_SPEED_PART;

	setYPosition(generateYPosition());
	generateGap();

	colliders_.push_back(&collider_);
	colliders_.push_back(&collider_reverse_);
}

unsigned Obstacle::generateYPosition() {
	return rand() %
		static_cast<unsigned>(Game::height - (sprite_height_ * 2 + gap_height_ + Game::height / FLOOR_SIDE_PART)) +
		static_cast<unsigned>(sprite_height_);
}

unsigned Obstacle::getYPosition() {
	return position_y_;
}

void Obstacle::setYPosition(unsigned value) {
	position_y_ = value;
}

void Obstacle::setIsMove(bool value) {
	is_move_ = value;
}

const std::vector<RectCollider*>& Obstacle::getCollider() {
	return colliders_;
}

void Obstacle::update() {
	if (is_move_) {
		position_x_ -= speed_ * Game::deltaTime;

		sprite_.setPosition(position_x_, sprite_.getPosition().y);
		rect_.setPosition(position_x_, rect_.getPosition().y);

		sprite_reverse_.setPosition(position_x_, sprite_reverse_.getPosition().y);
		rect_reverse_.setPosition(position_x_, rect_reverse_.getPosition().y);

		collider_.x0 = collider_reverse_.x0 = collider_.x1 = collider_reverse_.x1 = position_x_;
		collider_.x2 = collider_reverse_.x2 = collider_.x3 = collider_reverse_.x3 = position_x_ + sprite_width_;
	}
}

void Obstacle::fixedUpdate() {
	if (sprite_.getPosition().x < -1 * sprite_width_) {
		generateGap();
	}
}

void Obstacle::draw(RenderTarget& target, RenderStates states) const {
	target.draw(sprite_, states);
	target.draw(rect_, states);
	target.draw(sprite_reverse_, states);
	target.draw(rect_reverse_, states);
}