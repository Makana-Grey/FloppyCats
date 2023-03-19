#include <SFML/Graphics.hpp>
#include "Scene.hpp"

using namespace sf;

#ifndef _game_hpp
#define _game_hpp

class Game {
private:
	static inline Scene* pre_current_scene_ = nullptr;
	static inline Scene* pre_static_scene_ = nullptr;
	static inline Scene* current_scene_ = new Scene();
	static inline Scene* static_scene_ = new Scene();
	static inline Texture* sprite_list_ = nullptr;


	static inline Clock clock_;
	static inline bool is_kill_ = false;
	static inline bool is_load_scene_ = false;
	static inline bool is_load_static_scene_ = false;

	static void render();
	static void _kill();
	static void _loadScene();
	static void _loadStaticScene();
public:
	static inline RenderWindow* window;
	static inline unsigned width;
	static inline unsigned height;
	static inline Color backgroundColor = Color::Magenta;

	static inline double deltaTime;
	static inline double fixedDeltaTime;


	static void run();
	static void kill();
	static void loadScene(Scene* scene);
	static void loadStaticScene(Scene* scene);

	static const Texture& getSpriteList();
	static void setSpriteList(Texture& texture);
};

#endif // !_game_hpp
