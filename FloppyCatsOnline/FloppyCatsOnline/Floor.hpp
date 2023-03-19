#include "GameObject.hpp"
#include "Collidable.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

#ifndef _floor_hpp
#define _floor_hpp

class Floor : public GameObject, public Collidable<float> {
private:
	std::vector<Sprite*> sprites_;
	float speed_ = 0;
	float width_;
	float collider_y_ = 0;
public:
	Floor();
	virtual const float& getCollider() override;
	virtual void update() override;
	virtual void fixedUpdate() override;
	virtual void draw(RenderTarget& target, RenderStates states) const override;
};

#endif // !_floor_hpp