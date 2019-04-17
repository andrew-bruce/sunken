
#include <engine.hh>

#include "sunken.hh"

SceneTest scene_test;

int main()
{
	engine::start(1280, 720, "Sunken", &scene_test);
}