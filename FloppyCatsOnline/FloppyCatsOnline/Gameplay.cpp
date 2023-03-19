#include "Game.hpp"
#include "Gameplay.hpp"
#include "definitions.hpp"
#include <cmath>
#include <algorithm>

float collideSquare(float x1, float y1, const RectCollider& oc) {
	return
		0.5 * std::abs((oc.x0 - x1) * (oc.y1 - y1) - (oc.x1 - x1) * (oc.y0 - y1)) +
		0.5 * std::abs((oc.x1 - x1) * (oc.y2 - y1) - (oc.x2 - x1) * (oc.y1 - y1)) +
		0.5 * std::abs((oc.x2 - x1) * (oc.y3 - y1) - (oc.x3 - x1) * (oc.y2 - y1)) +
		0.5 * std::abs((oc.x3 - x1) * (oc.y0 - y1) - (oc.x0 - x1) * (oc.y3 - y1));
}

bool Gameplay::isCollide(const RectCollider& player_collider, const RectCollider& obstacle_collider,
	float obstacle_collider_y, float obstacle_square, float player_square) {

	return
		!std::round(obstacle_square - collideSquare(player_collider.x3, player_collider.y3, obstacle_collider)) ||
		!std::round(obstacle_square - collideSquare(player_collider.x2, player_collider.y2, obstacle_collider)) ||
		!std::round(player_square - collideSquare(obstacle_collider.x3, obstacle_collider_y, player_collider)) ||
		!std::round(player_square - collideSquare(obstacle_collider.x0, obstacle_collider_y, player_collider)) ||
		!std::round(obstacle_square - collideSquare(player_collider.x1, player_collider.y1, obstacle_collider)) ||
		!std::round(obstacle_square - collideSquare(player_collider.x0, player_collider.y0, obstacle_collider));
}

float Gameplay::calcSquare(const RectCollider& collider) {
	return
		std::sqrt(std::pow(collider.x0 - collider.x1, 2) + std::pow(collider.y0 - collider.y1, 2)) *
		std::sqrt(std::pow(collider.x0 - collider.x3, 2) + std::pow(collider.y0 - collider.y3, 2));
}

void Gameplay::initObjects() {
	player = new Player(Game::height / PLAYER_Y_OFFSET_PART, PLAYER_COLOR);
	obstacle = new Obstacle();
	floor = new Floor();
}

Gameplay::Gameplay() {
	initObjects();

	player_square = calcSquare(player->getCollider());
	obstacle_0_square = calcSquare(*obstacle->getCollider()[0]);
	obstacle_1_square = calcSquare(*obstacle->getCollider()[1]);

	auto oc = *obstacle->getCollider()[1];
	collide_offset = (oc.x3 - oc.x0) * OBSTACLE_COLLIDE_OFFSET_FACTOR;
}

void Gameplay::defineCollisions(Player& player) {
	if (player.getState() != Wait) {
		auto pc = player.getCollider();

		if (player.getState() != Dead) {
			auto oc = obstacle->getCollider();

			if (std::max(pc.x2, pc.x3) - oc[0]->x0 >= collide_offset) {
				if (std::min(pc.y1, pc.y2) - oc[0]->y0 < oc[1]->y1 - std::max(pc.y0, pc.y3)) {
					if (isCollide(pc, *oc[0], oc[0]->y0, obstacle_0_square, player_square)) {
						onCollideWithObstacle();
					}
				}
				else {
					if (isCollide(pc, *oc[1], oc[1]->y1, obstacle_1_square, player_square)) {
						onCollideWithObstacle();
					}
				}
			}
		}

		if (pc.y3 - floor->getCollider() > FLOOR_COLLIDE_OFFSET) {
			onCollideWithFloor();
		}
	}
}

void Gameplay::definePassObstacle(Player& player) {
	if (player.getState() != Dead || player.getState() != Wait) {
		auto pc = player.getCollider();
		auto oc = obstacle->getCollider();

		if (std::min(pc.x0, pc.x1) > oc[0]->x3) {
			if (!is_pass_obstacle_) {
				onPassObstacle();
			}
			is_pass_obstacle_ = true;
		}
		else {
			is_pass_obstacle_ = false;
		}
	}
}