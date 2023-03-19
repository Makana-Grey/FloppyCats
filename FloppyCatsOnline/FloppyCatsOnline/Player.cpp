#include "Player.hpp"
#include "Game.hpp"
#include "definitions.hpp"
#include <cmath>

void Player::stateInit() {
	jump_height_base_ = Game::height / PLAYER_JUMP_HEIGHT_SIDE_PART;
	jump_height_ = jump_height_base_;
	jump_speed_base_ = Game::height / PLAYER_JUMP_SPEED_HEIGHT_PART;
	jump_speed_ = jump_speed_base_;
	drop_speed_base_ = Game::height / PLAYER_DROP_SPEED_HEIGHT_PART;
	drop_speed_ = drop_speed_base_;
}

void Player::animate() {
	if (is_animate_ && animation_duration_ > PLAYER_ANIM_DURATION) {
		animtion_frame_ = (animtion_frame_ + 1) % PLAYER_ANIM_FRAMES_COUNT;
		sprite_.setTextureRect(IntRect(
			PLAYER_X + (PLAYER_WIDTH * animtion_frame_),
			PLAYER_Y,
			PLAYER_WIDTH,
			PLAYER_HEIGHT
		));
		animation_duration_ = 0;
	}
	animation_duration_ += Game::fixedDeltaTime;
}

void Player::up() {
	jump_speed_ = jump_speed_base_ / 2 +
		(jump_speed_base_ / 2) * ((jump_height_ * jump_height_) / (jump_height_base_ * jump_height_base_));
	jump_height_ -= jump_speed_ * Game::deltaTime;

	if (sprite_.getPosition().y > height_ / 2) {
		sprite_.setPosition(sprite_.getPosition().x, sprite_.getPosition().y - jump_speed_ * Game::deltaTime);
	}


	if (jump_height_ < 0) {
		jump_height_ = jump_height_base_;
		jump_speed_ = jump_speed_base_;
		state_ = Drop;
	}

	rotation_ -= PLAYER_ROTATION_UP_SPEED * Game::deltaTime;
	rotation_ = rotation_ > -PLAYER_ROTATION_UP_BUOND ? rotation_ : -PLAYER_ROTATION_UP_BUOND;
	sprite_.setRotation(rotation_);
}

void Player::down() {
	drop_speed_ = drop_speed_base_ -
		(drop_speed_base_ / 2) * ((jump_height_base_ * jump_height_base_) / (jump_height_ * jump_height_));
	jump_height_ += drop_speed_ * Game::deltaTime;

	sprite_.setPosition(sprite_.getPosition().x, sprite_.getPosition().y + drop_speed_ * Game::deltaTime);

	rotation_ += PLAYER_ROTATION_DOWN_SPEED * Game::deltaTime;
	rotation_ = rotation_ < PLAYER_ROTATION_DOWN_BUOND ? rotation_ : PLAYER_ROTATION_DOWN_BUOND;
	sprite_.setRotation(rotation_);
}

void Player::crash() {
	down();
	sprite_.setPosition(
		sprite_.getPosition().x - (drop_speed_base_ - drop_speed_) * PLAYER_CRASH_FACTOR * Game::deltaTime,
		sprite_.getPosition().y
	);
}

Player::Player() {
	sprite_.setTexture(Game::getSpriteList());
	sprite_.setTextureRect(IntRect(PLAYER_X, PLAYER_Y, PLAYER_WIDTH, PLAYER_HEIGHT));

	float factor = 1.f * Game::width / PLAYER_SIDE_PART / PLAYER_WIDTH;

	sprite_.setScale(factor, factor);
	sprite_.setPosition(
		PLAYER_WIDTH * factor * 2,
		Game::height / 2. - (PLAYER_HEIGHT * factor) / 2
	);

	stateInit();

	width_ = PLAYER_WIDTH * factor;
	height_ = PLAYER_HEIGHT * factor;
	diameter_ = std::sqrtf(std::powf(width_, 2) + std::powf(height_, 2));
	diameter_alpha_ = std::atanf(height_ / width_) * 180 / 3.14159265;
}

Player::Player(const float y_offset, const unsigned color_filter) : Player() {
	sprite_.setPosition(
		sprite_.getPosition().x,
		sprite_.getPosition().y + y_offset
	);

	sprite_.setColor(Color(color_filter));
}

void Player::wait() {
	state_ = Wait;
}

void Player::jump() {
	state_ = Jump;
	jump_height_ = jump_height_base_;
}

void Player::dead() {
	state_ = Dead;
	jump_height_ = jump_height_base_;
}

void Player::setIsAnimate(bool value) {
	is_animate_ = value;
}

PlayerState Player::getState() {
	return state_;
}

const RectCollider& Player::getCollider() {
	const float radian_factor = 0.0174533;

	collider_.x1 = sprite_.getPosition().x;
	collider_.y1 = sprite_.getPosition().y;

	float curr_radian = (-90 - rotation_) * radian_factor;
	collider_.x0 = collider_.x1 + height_ * std::cosf(curr_radian);
	collider_.y0 = collider_.y1 - height_ * std::sinf(curr_radian);

	curr_radian = -rotation_ * radian_factor;
	collider_.x2 = collider_.x1 + width_ * std::cosf(curr_radian);
	collider_.y2 = collider_.y1 - width_ * std::sinf(curr_radian);

	curr_radian = (-diameter_alpha_ - rotation_) * radian_factor;
	collider_.x3 = collider_.x1 + diameter_ * std::cosf(curr_radian);
	collider_.y3 = collider_.y1 - diameter_ * std::sinf(curr_radian);

	return collider_;
}

void Player::update() {
	switch (state_)
	{
	case Drop:
		down();
		break;
	case Jump:
		up();
		break;
	case Wait:
		return;
	case Dead:
		crash();
		break;
	default:
		break;
	}
}

void Player::fixedUpdate() {
	animate();
}

void Player::draw(RenderTarget& target, RenderStates states) const {
	target.draw(sprite_, states);
}