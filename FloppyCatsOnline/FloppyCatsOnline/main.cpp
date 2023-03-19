#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Scene.hpp"
#include "Background.hpp"
#include "Menu.hpp"
#include "Singleplayer.hpp"
#include "Multiplayer.hpp"
#include "GameSettings.hpp"

#include "path.hpp"
#include "definitions.hpp"

#include <stdlib.h>
#include <time.h>

using namespace sf;

#ifdef _DEBUG 
unsigned const
FULLSCREEN_MODE_ID = 3,
SCREEN_STYLE = Style::Titlebar | Style::Close;
#else 
unsigned const
FULLSCREEN_MODE_ID = 0,
SCREEN_STYLE = Style::Titlebar | Style::Close | Style::Fullscreen;
#endif 

int main()
{
	srand(time(NULL));

	VideoMode fullscreen_mode = VideoMode::getFullscreenModes()[FULLSCREEN_MODE_ID];

	if (fullscreen_mode.isValid()) {
		Game::window = new RenderWindow(fullscreen_mode, "Floppy Cats Online", SCREEN_STYLE);

#ifdef NDEBUG 
		Game::window->setMouseCursorVisible(false);
#endif 
		const auto media = combine_paths(get_current_path(), MEDIA_FOLDER);

		auto icon = Image();
		if (icon.loadFromFile(combine_paths(media, ICON_FILE))) {
			Game::window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		}
		Texture* texture = new Texture();
		if (!texture->loadFromFile(combine_paths(media, SPRITE_LIST_FILE))) {
			return 1;
		} 

		Game::width = fullscreen_mode.width;
		Game::height = fullscreen_mode.height;
		Game::backgroundColor = Color(GAME_BACKGROUND_COLOR);
		Game::setSpriteList(*texture);

		Scene* backgroundScene = new Scene();
		backgroundScene->gameObjects.push_back(new Background());

		Game::loadStaticScene(backgroundScene);

#if MODE == DEPLOY
		Game::loadScene(new Menu());
#endif
#if MODE == MENU
		Game::loadScene(new Menu());
#endif
#if MODE == SINGLEPLAYER
		Game::loadScene(new Singleplayer());
#endif
#if MODE == MULTIPLAYER
		Game::loadScene(new Multiplayer());
#endif
#if MODE == GAME_SETTINGS
		Game::loadScene(new GameSettings());
#endif

		Game::run();

		return 0;
	}

	return 1;
}