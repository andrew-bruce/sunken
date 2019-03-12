#include "scene.hh"



void Scene::update(const float& delta_time)
{
	entities_.update(delta_time);
}

void Scene::render()
{
	entities_.render();
}