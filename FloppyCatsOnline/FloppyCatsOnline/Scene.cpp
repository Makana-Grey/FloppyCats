#include "Scene.hpp"

Scene::~Scene() {
	for (auto go : this->gameObjects) {
		delete go;
	}
	gameObjects.clear();
}

void Scene::update() {
	for (auto go : this->gameObjects) {
		go->update();
	}
}

void Scene::fixedUpdate() {
	for (auto go : this->gameObjects) {
		go->fixedUpdate();
	}
}

void Scene::draw(RenderTarget& target, RenderStates states) const {
	for (auto go : this->gameObjects) {
		target.draw(*go, states);
	}
}