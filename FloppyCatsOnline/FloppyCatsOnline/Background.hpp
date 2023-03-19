#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

#ifndef _background_hpp
#define _background_hpp

class Background : public GameObject {

private:
	unsigned star_space_ = 1;
	unsigned star_spaces_count_x_ = 1;
	unsigned star_spaces_count_y_ = 1;
	float stars_speed_ = 1;
	unsigned parallax_level_ = 1;
	std::vector<RectangleShape*> stars_;
public:
	Background();
	~Background();
	virtual void update() override;
	virtual void fixedUpdate() override;
	virtual void draw(RenderTarget& target, RenderStates states) const override;
};

#endif // !_background_hpp