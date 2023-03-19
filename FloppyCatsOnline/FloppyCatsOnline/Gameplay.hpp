#include "Collidable.hpp"
#include "Player.hpp"
#include "Obstacle.hpp"
#include "Floor.hpp"
#include <SFML/Graphics.hpp>


#ifndef _gameplay_hpp
#define _gameplay_hpp

class Gameplay {
private:
	bool is_pass_obstacle_ = false;

protected:
	Player* player;
	Obstacle* obstacle;
	Floor* floor;

	float action_duration = 0;

	float player_square = 0;
	float obstacle_0_square = 0;
	float obstacle_1_square = 0;
	float collide_offset = 0;

	bool is_over = false;

	virtual bool isCollide(const RectCollider& player_collider, const RectCollider& obstacle_collider,
		float ocy, float obstacle_square, float player_square);
	virtual float calcSquare(const RectCollider& collider);

	virtual void initObjects();

	virtual void onCollideWithObstacle() {};
	virtual void onCollideWithFloor() {};
	virtual void onPassObstacle() {};

public: 
	Gameplay();

	void defineCollisions(Player& player);
	void definePassObstacle(Player& player);
};

#endif // !_gameplay_hpp
