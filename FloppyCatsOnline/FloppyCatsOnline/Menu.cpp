#include "Game.hpp"
#include "Menu.hpp"
#include "MenuButton.hpp"
#include "Logo.hpp"
#include "TextObject.hpp"
#include "Singleplayer.hpp"
#include "Multiplayer.hpp"
#include "GameSettings.hpp"
#include "definitions.hpp"

enum Actions {
	RunSingleplayer = 0,
	RunMultiplayer = 1,
	ShowGameSettings = 2,
	KillGame = 3,
};

void Menu::setActions() {
	for (unsigned i = 0; i < menu_buttons_count_; i++)
	{
		MenuButton* mb = (MenuButton*)gameObjects[i];
		switch (i)
		{
		case RunSingleplayer:
			mb->onClick = []() { Game::loadScene(new Singleplayer()); };
			break;
		case RunMultiplayer:
			mb->onClick = []() { Game::loadScene(new Multiplayer()); };
			break;
		case ShowGameSettings:
			mb->onClick = []() { Game::loadScene(new GameSettings()); };
			break;
		case KillGame:
			mb->onClick = []() { Game::kill(); };
			break;
		default:
			break;
		}
	}
}

void Menu::setCurrent() {
	for (unsigned i = 0; i < menu_buttons_count_; i++)
	{
		MenuButton* mb = (MenuButton*)gameObjects[i];
		mb->setIsActive(i == current_button_);
	}
}


Menu::Menu() : menu_buttons_count_(4) {
	float factor_x_y = 1;

	if (Game::height <= Game::width) {
		factor_x_y = Game::height / MENU_BUTTONS_SIDE_PART;
		factor_x_y /= MENU_BUTTONS_HEIGHT;
	}
	else {
		factor_x_y = Game::width / MENU_BUTTONS_SIDE_PART;
		factor_x_y /= MENU_BUTTONS_WIDTH;
	}

	float button_height = factor_x_y * MENU_BUTTONS_HEIGHT;
	float padding = button_height / 10;

	float common_height = button_height * menu_buttons_count_ + padding * (menu_buttons_count_ - 1);
	if (common_height > Game::height) {
		factor_x_y *= Game::height / common_height;
		button_height = factor_x_y * MENU_BUTTONS_HEIGHT;
		padding = button_height / 10;
		common_height = button_height * menu_buttons_count_ + padding * (menu_buttons_count_ - 1);
	}

	float start_position_y = (Game::height - common_height) / 2.f;

	for (unsigned i = 0; i < 4; i++)
	{
		gameObjects.push_back(new MenuButton(
			IntRect(MENU_BUTTONS_START_X + MENU_BUTTONS_WIDTH * i, 0, MENU_BUTTONS_WIDTH, MENU_BUTTONS_HEIGHT),
			IntRect(MENU_BUTTONS_START_X + MENU_BUTTONS_WIDTH * i, MENU_BUTTONS_HEIGHT, MENU_BUTTONS_WIDTH, MENU_BUTTONS_HEIGHT),
			Vector2f(padding * 10, start_position_y + i * (button_height + padding)),
			factor_x_y
		));
	}

	setActions();
	setCurrent();

	gameObjects.push_back(new Logo(
		IntRect(LOGO_START_X, 0, LOGO_WIDTH, LOGO_HEIGHT),
		Vector2f(
			Game::width - ((Game::width - (MENU_BUTTONS_WIDTH * factor_x_y + padding * 10)) / 2) - LOGO_WIDTH * factor_x_y * 0.85 / 2,
			Game::height / 2 - LOGO_HEIGHT * factor_x_y * 0.85 / 2 + 10
		),
		factor_x_y * 0.85
	));

	auto factor = Game::height / MENU_META_SIDE_PART;

	gameObjects.push_back(new TextObject(
		MENU_META,
		Vector2f(factor, Game::height - (factor * 2)),
		factor / CHARS_HEIGHT,
		Color(0x0ff5dff)
	));
}

void Menu::fixedUpdate() {
	if (focus_duration_ > MENU_SWITCH_DURATION) {
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
			current_button_ = ((current_button_ - 1) + menu_buttons_count_) % menu_buttons_count_;
			setCurrent();
			focus_duration_ = 0;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
			current_button_ = (current_button_ + 1) % menu_buttons_count_;
			setCurrent();
			focus_duration_ = 0;
		}
	}
	focus_duration_ += Game::fixedDeltaTime;

	Scene::fixedUpdate();
}