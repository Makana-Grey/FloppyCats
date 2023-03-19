#include "Scene.hpp"
#include "Gameplay.hpp"
#include "TextObject.hpp"
#include <SFML/Graphics.hpp>

#ifndef _singleplayer_hpp
#define _singleplayer_hpp

class Singleplayer : public Scene, public Gameplay {
private:
	TextObject* text_;

	unsigned score_ = 0;
	bool is_reset_ = false;

public:
	Singleplayer();
	virtual void update() override;
	virtual void fixedUpdate() override;
	virtual void freeWindow() override;
	virtual void onCollideWithObstacle() override;
	virtual void onCollideWithFloor() override;
	virtual void onPassObstacle() override;
};

#endif // !_singleplayer_hpp