#include "Scene.hpp"
#include <SFML/Graphics.hpp>

#ifndef _menu_hpp
#define _menu_hpp

class Menu : public Scene {
private:
	const unsigned menu_buttons_count_;
	signed current_button_ = 0;
	float focus_duration_ = 0;

	void setActions();
	void setCurrent();
public:
	Menu();
	virtual void fixedUpdate() override;
};

#endif // !_menu_hpp