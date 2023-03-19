#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

using namespace sf;

#ifndef _menu_button_hpp
#define _menu_button_hpp

class MenuButton : public GameObject {
private:
	Sprite sprite_;
	const IntRect texture_rect_active_;
	const IntRect texture_rect_passive_;

	bool is_setted_ = false;
	bool is_active_ = false;

public:
	std::function<void()> onClick = []() {};

	MenuButton(const IntRect& texture_rect_active, const IntRect& texture_rect_passive,
		const Vector2f& position, const float factor_x_y);

	bool getIsActive();
	void setIsActive(bool value);

	virtual void fixedUpdate() override;
	virtual void draw(RenderTarget& target, RenderStates states) const override;
};

#endif // !_menu_button_hpp