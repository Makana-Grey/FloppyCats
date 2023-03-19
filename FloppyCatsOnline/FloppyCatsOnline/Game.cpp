#include "Game.hpp"
#include "definitions.hpp"


void Game::render() {
	Game::deltaTime = Game::clock_.restart().asMicroseconds() * 1e-6;
	Game::fixedDeltaTime += Game::deltaTime;


	Game::window->clear(Game::backgroundColor);

	Game::static_scene_->update();
	Game::current_scene_->update();

	if (Game::fixedDeltaTime >= FIXED_DELTA_TIME) {
		Game::static_scene_->fixedUpdate();
		Game::current_scene_->fixedUpdate();
		Game::fixedDeltaTime = 0;
	}

	Game::window->draw(*Game::static_scene_);
	Game::window->draw(*Game::current_scene_);


	Game::window->display();

	Game::static_scene_->freeWindow();
	Game::current_scene_->freeWindow();
}

void Game::run() {
	while (Game::window->isOpen())
	{
		Event event;
		while (Game::window->pollEvent(event) || Game::is_kill_)
		{
			if (event.type == sf::Event::Closed || Game::is_kill_)
			{
				Game::_kill();
				return;
			}
		}

		if (Game::is_load_scene_) {
			Game::_loadScene();
		}

		if (Game::is_load_static_scene_) {
			Game::_loadStaticScene();
		}

		render();
	}
}


void Game::_kill() {
	delete Game::current_scene_;
	delete Game::static_scene_;
	delete Game::sprite_list_;
	delete Game::window;
}

void Game::kill() {
	Game::is_kill_ = true;
}


void Game::_loadScene() {
	Scene* old_scene = Game::current_scene_;
	Game::current_scene_ = Game::pre_current_scene_;
	Game::pre_current_scene_ = nullptr;
	delete old_scene;
	Game::is_load_scene_ = false;
}

void Game::loadScene(Scene* scene) {
	Game::pre_current_scene_ = scene;
	Game::is_load_scene_ = true;
}

void Game::_loadStaticScene() {
	Scene* old_scene = Game::static_scene_;
	Game::static_scene_ = Game::pre_static_scene_;
	Game::pre_current_scene_ = nullptr;
	delete old_scene;
	Game::is_load_static_scene_ = false;
}

void Game::loadStaticScene(Scene* scene) {
	Game::pre_static_scene_ = scene;
	Game::is_load_static_scene_ = true;
}


const Texture& Game::getSpriteList() {
	return *Game::sprite_list_;
}

void Game::setSpriteList(Texture& texture) {
	Game::sprite_list_ = &texture;
}