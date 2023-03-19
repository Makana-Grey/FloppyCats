#include "GameObject.hpp"
#include "Collidable.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

#ifndef _obstacle_hpp
#define _obstacle_hpp

class Obstacle : public GameObject, public Collidable<std::vector<RectCollider*>> {
private:
	Sprite sprite_;
	Sprite sprite_reverse_;
	RectangleShape rect_;
	RectangleShape rect_reverse_;
	float sprite_width_ = 0;
	float sprite_height_ = 0;

	std::vector<RectCollider*> colliders_;
	RectCollider collider_;
	RectCollider collider_reverse_;

	bool is_move_ = false;

	float gap_height_ = 0;

	float speed_ = 0;
	float position_x_ = 0;
	unsigned position_y_ = 0;

	void generateGap();
public:
	Obstacle();
	void setIsMove(bool value);
	unsigned generateYPosition();
	unsigned getYPosition();
	void setYPosition(unsigned value);
	virtual const std::vector<RectCollider*>& getCollider() override;
	virtual void update() override;
	virtual void fixedUpdate() override;
	virtual void draw(RenderTarget& target, RenderStates states) const override;
};

#endif // !_obstacle_hpp