#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

#ifndef _logo_hpp
#define _logo_hpp

class Logo : public GameObject {
private:
	Sprite sprite_;

public:
	Logo(const IntRect& texture_rect, const Vector2f& position, const float factor_x_y);

	virtual void draw(RenderTarget& target, RenderStates states) const override;
};

#endif // !_logo_hpp