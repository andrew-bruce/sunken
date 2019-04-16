#include <array>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>

#include <physics.hh>
#include <renderer.hh>
#include <level_loader.hh>
#include <ecm.hh>

#include "scenes/scene_test.hh"

#include "sunken.hh"

// Window
std::size_t game_width;
std::size_t game_height;

// Keyboard
std::array<bool, sf::Keyboard::KeyCount> keyboard;

//// TEST
SceneTest scene_test;

void load(sf::RenderWindow& window)
{
	srand(time(NULL));

	std::cout << "Initialising renderer..." << std::endl;
	renderer::initialise(window);

	std::cout << "Loading font..." << std::endl;
	font.loadFromFile("res/fonts/FiraCode-Regular.ttf");

	scene_test.load();
}

void input(sf::RenderWindow& window)
{
	sf::Event event{};

	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed)
			window.close();

		else if (
				event.type == sf::Event::KeyPressed &&
				event.key.code != sf::Keyboard::Unknown)
			keyboard[event.key.code] = true;

		else if (
				event.type == sf::Event::KeyReleased &&
				event.key.code != sf::Keyboard::Unknown)
			keyboard[event.key.code] = false;

	if (keyboard[sf::Keyboard::Escape])
		window.close();
}

void update()
{
	// Handle time with fixed step and accumulator for variable framerate
	static const float delta_time(1.0f / 100.0f);

	static sf::Clock clock;
	static float accumulator(0.0f);
	accumulator += clock.restart().asSeconds();

	while (accumulator >= delta_time) {
		accumulator -= delta_time;

		scene_test.update(delta_time);
		renderer::update(delta_time);
	}
}

void render()
{
	scene_test.render();
	renderer::render();
}

void unload(sf::RenderWindow& window)
{
	scene_test.unload();
	renderer::shutdown();
}

int main(void)
{
	// Window
	game_width  = 1280;//sf::VideoMode::getDesktopMode().width;
	game_height = 720; //sf::VideoMode::getDesktopMode().height;
	std::cout << "Resolution detected: "
		<< game_width << 'x' << game_height << std::endl;
	sf::RenderWindow window(sf::VideoMode(game_width, game_height), "Sunken");

	// Game loop
	load(window);
	while (window.isOpen())
	{
		input(window);
		update();
		render();
	}
	unload(window);
}
