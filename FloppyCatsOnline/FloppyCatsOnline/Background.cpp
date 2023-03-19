#include "Background.hpp"
#include "Game.hpp"
#include <algorithm>
#include <stdlib.h>

using namespace sf;

void generatePosition(Transformable* t, unsigned start_position, unsigned star_space,
	unsigned spaces_count_x, unsigned spaces_count_y) {
	t->setPosition(
		start_position + (rand() % spaces_count_x) * star_space + rand() % star_space,
		(rand() % spaces_count_y) * star_space + rand() % star_space
	);
}


void initStarsBaseProps(unsigned& star_space, unsigned& spaces_count_x, unsigned& spaces_count_y,
	unsigned w, unsigned h) {
	star_space = std::max(w, h) / 12;
	if (!star_space) {
		star_space = 1;
	}

	spaces_count_x = w / star_space + 1;
	spaces_count_y = h / star_space + 1;
}

void initStarsPositions(std::vector<RectangleShape*>& stars, unsigned star_space, unsigned spaces_count_x,
	unsigned spaces_count_y, unsigned w, unsigned h) {

	unsigned star_size = std::min(w, h) / 200;
	if (!star_size) {
		star_size = 1;
	}

	unsigned stars_count_in_third = (
		(spaces_count_x - (rand() % (spaces_count_x / 4))) *
		(spaces_count_y - (rand() % (spaces_count_y / 3)))
		) / 3;

	for (unsigned i = 0; i < 3; i++)
	{
		unsigned start_position = i * (w / 3) - (i == 2 ? star_space : 0);
		unsigned current_spaces_x = (spaces_count_x / 3) + (i % 2 ? 0 : 2);

		for (unsigned j = 0; j < stars_count_in_third; j++)
		{
			unsigned size = star_size * (rand() % 2 + 1);
			RectangleShape* star = new RectangleShape(Vector2f(size, size));

			generatePosition(star, start_position, star_space, current_spaces_x, spaces_count_y);
			stars.push_back(star);
		}
	}
}

void initStarsSpeedProps(float& first_speed, unsigned& parallax_level, unsigned star_space) {
	first_speed = Game::width * 0.6;

	parallax_level = first_speed / 48;
	if (!parallax_level) {
		parallax_level = 1;
	}
}


Background::Background() {
	initStarsBaseProps(star_space_, star_spaces_count_x_, star_spaces_count_y_, Game::width, Game::height);
	initStarsPositions(stars_, star_space_, star_spaces_count_x_, star_spaces_count_y_, Game::width, Game::height);
	initStarsSpeedProps(stars_speed_, parallax_level_, star_space_);
}

Background::~Background() {
	for (auto star : stars_) {
		delete star;
	}
	stars_.clear();
}


void Background::update() {
	for (unsigned i = 0; i < stars_.size(); i++)
	{
		auto star = stars_[i];
		star->setPosition(
			star->getPosition().x - (stars_speed_ / (i % parallax_level_ + 1)) * Game::deltaTime,
			star->getPosition().y
		);
	}
}

void Background::fixedUpdate() {
	for (auto star : stars_)
	{
		if (star->getPosition().x < -1 * star->getSize().x) {
			generatePosition(star, Game::width, star_space_, 1, star_spaces_count_y_);
		}
	}
}

void Background::draw(RenderTarget& target, RenderStates states) const
{
	for (auto star : stars_) {
		target.draw(*star, states);
	}
}