#include <SFML/Graphics.hpp>

using namespace sf;

#ifndef _game_object_hpp
#define _game_object_hpp

class GameObject : public Drawable {
public:
	virtual void update() {};
	virtual void fixedUpdate() {};
};

#endif // !_game_object_hpp