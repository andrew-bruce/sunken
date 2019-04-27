
#include <engine.hh>

#include "sunken.hh"

SceneGame scene_game;
SceneMenu scene_menu;
SceneInstructions scene_instructions;

int main()
{
	srand(time(nullptr));
	engine::start("Sunken", 1280, 720, &scene_menu);
}
