
#include <engine.hh>

#include "sunken.hh"

SceneGame scene_game;

int main()
{
	engine::start("Sunken", 1280, 720, &scene_game);
}