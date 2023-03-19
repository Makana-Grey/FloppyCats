#include "Game.hpp"
#include "MenuButton.hpp"

MenuButton::MenuButton(const IntRect& texture_rect_active, const IntRect& texture_rect_passive,
	const Vector2f& position, const float factor_x_y)
	: texture_rect_active_(texture_rect_active), texture_rect_passive_(texture_rect_passive) {
	sprite_.setTexture(Game::getSpriteList());
	sprite_.setTextureRect(texture_rect_passive);
	sprite_.setPosition(position);
	sprite_.setScale(factor_x_y, factor_x_y);
}

bool MenuButton::getIsActive() {
	return is_active_;
}
void MenuButton::setIsActive(bool value) {
	if (is_active_ != value) {
		is_active_ = value;
		is_setted_ = false;
	}
}

void MenuButton::fixedUpdate() {
	if (!is_setted_) {
		if (is_active_) {
			sprite_.setTextureRect(texture_rect_active_);
		}
		else {
			sprite_.setTextureRect(texture_rect_passive_);
		}
		is_setted_ = true;
	}
	if (is_active_ && Keyboard::isKeyPressed(Keyboard::Enter)) {
		onClick();
	}
}

void MenuButton::draw(RenderTarget& target, RenderStates states) const {
	target.draw(sprite_, states);
}