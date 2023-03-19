#include "Logo.hpp"
#include "Game.hpp"

Logo::Logo(const IntRect& texture_rect, const Vector2f& position, const float factor_x_y) {
	sprite_.setTexture(Game::getSpriteList());
	sprite_.setTextureRect(texture_rect);
	sprite_.setPosition(position);
	sprite_.setScale(factor_x_y, factor_x_y);
}

void Logo::draw(RenderTarget& target, RenderStates states) const {
	target.draw(sprite_, states);
}