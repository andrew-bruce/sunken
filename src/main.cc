
#include <engine.hh>

#include "sunken.hh"

SceneGame scene_game;
SceneMenu scene_menu;
SceneInstructions scene_instructions;

int main()
{
	srand(time(nullptr));
	auto video_mode = sf::VideoMode::getDesktopMode();
	auto size = sf::Vector2f(video_mode.width, video_mode.height) * 0.8f;
	engine::start("Sunken", size.x, size.y, &scene_menu);
}
