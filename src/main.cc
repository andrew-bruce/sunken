
#include <engine.hh>

#include "sunken.hh"

SceneGame scene_game;
SceneMenu scene_menu;

int main()
{
	srand(time(nullptr));
	engine::start("Sunken", 1280, 720, &scene_game);
}
