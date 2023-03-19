#include "GameObject.hpp"
#include "Collidable.hpp"
#include <SFML/Graphics.hpp>

#ifndef _player_hpp
#define _player_hpp

enum PlayerState {
	Drop,
	Jump,
	Wait,
	Dead,
};

class Player : public GameObject, public Collidable<RectCollider> {
private:
	Sprite sprite_;
	PlayerState state_ = Wait;
	RectCollider collider_;

	float jump_height_base_ = 0;
	float jump_height_ = 0;
	float jump_speed_ = 0;
	float jump_speed_base_ = 0;
	float drop_speed_ = 0;
	float drop_speed_base_ = 0;

	float rotation_ = 0;
	float width_ = 0;
	float height_ = 0;
	float diameter_ = 0;
	float diameter_alpha_ = 0;

	bool is_animate_ = true;
	signed animtion_frame_ = 0;
	float animation_duration_ = 0;

	void stateInit();
	void animate();
	void up();
	void down();
	void crash();
public:
	Player();
	Player(const float y_offset, const unsigned color_filter);
	void wait();
	void jump();
	void dead();
	PlayerState getState();
	void setIsAnimate(bool value);
	virtual const RectCollider& getCollider() override;
	virtual void update() override;
	virtual void fixedUpdate() override;
	virtual void draw(RenderTarget& target, RenderStates states) const override;
};

#endif // !_player_hpp
