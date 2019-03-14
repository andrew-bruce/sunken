// STD
#include <array>

// SFML
#include <SFML/Graphics.hpp>

// LIBRARIES
#include <system_renderer.hh>
#include <ecm.hh>
#include <cmp_shape.hh>

// GAME
#include "sunken.hh"



// Window
std::size_t game_width;
std::size_t game_height;

// Keyboard
std::array<bool, sf::Keyboard::KeyCount> keyboard;

// TEST
Entity entity;



void reset() {}

void load(sf::RenderWindow& window)
{
	Renderer::initialise(window);

	font.loadFromFile("res/fonts/FiraCode-Regular.ttf");

	CmpShape* shape = entity.add_component<CmpShape>();
	shape->use_shape<sf::CircleShape>(12.0f);

	reset();
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
	static sf::Clock clock;
	const float delta_time(clock.restart().asSeconds());

	entity.update(delta_time);

	Renderer::update(delta_time);
}

void render()
{
	entity.render();

	Renderer::render();
}

void unload(sf::RenderWindow& window)
{
	Renderer::shutdown();
}

int main(void)
{
	game_width = sf::VideoMode::getDesktopMode().width;
	game_height = sf::VideoMode::getDesktopMode().height;

	sf::RenderWindow window(sf::VideoMode(
		game_width,
		game_height),
		"Sunken");

	load(window);
	while (window.isOpen()) {
		input(window);
		update();
		render();
	}

	unload(window);
}