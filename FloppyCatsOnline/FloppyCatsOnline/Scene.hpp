#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

#ifndef _scene_hpp
#define _scene_hpp

class Scene : public GameObject {
public:
	std::vector<GameObject*> gameObjects;

	~Scene();
	virtual void update() override;
	virtual void fixedUpdate() override;
	virtual void draw(RenderTarget& target, RenderStates states) const override;
	virtual void freeWindow() {};
};

#endif // !_scene_hpp
