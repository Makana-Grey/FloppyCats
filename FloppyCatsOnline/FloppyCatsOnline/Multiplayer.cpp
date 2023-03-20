#include "Multiplayer.hpp"

Multiplayer::Multiplayer() {
	if (network_.initialize()) {
		network_.connect();
	}
}

void Multiplayer::update() {
	Scene::update();
}

void Multiplayer::fixedUpdate() {
	Scene::fixedUpdate();
}