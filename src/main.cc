// STD
#include <array>
#include <cstddef>
#include <iostream>

// SFML
#include <SFML/Graphics.hpp>

// LIBRARIES
#include <system_renderer.hh>
#include <level_system.hh>
#include <ecm.hh>
#include <cmp_shape.hh>

// GAME
#include "cmp_movement_player.hh"
#include "sunken.hh"



// Window
std::size_t game_width;
std::size_t game_height;

// Keyboard
std::array<bool, sf::Keyboard::KeyCount> keyboard;

//// TEST
Entity entity;
//// TEST



void reset() {}

void load(sf::RenderWindow& window)
{
	std::cout << "Initialising renderer..." << std::endl;
	renderer::initialise(window);

	std::cout << "Loading font..." << std::endl;
	font.loadFromFile("res/fonts/FiraCode-Regular.ttf");

	//// TEST
	level::load_level_file("res/levels/maze2.txt");
	if (!level::loaded())
		std::cout << "ERROR\n";
	auto list = level::find_tiles(level::Tile::Empty);
	std::cout << "Size:\t" << list.size() << std::endl;

	CmpShape* shape = entity.add_component<CmpShape>();
	shape->use_shape<sf::CircleShape>(12.0f);
	shape->shape().setOrigin(12.0f, 12.0f);
	entity.add_component<CmpMovementPlayer>();

	// Move to start tile or centre of screen
	std::vector<sf::Vector2ul> start_tiles(level::find_tiles(
		level::Tile::Start));
	if (start_tiles.size() != 0) {
		sf::Vector2f position(level::tile_position(
			start_tiles.front()));

		sf::Vector2f offset(
			level::tile_size() / 2.0f,
			level::tile_size() / 2.0f);

		entity.move_to(position + offset);
	} else
		entity.move_to(sf::Vector2f(
			game_width,
			game_height) / 2.0f);
	//// TEST

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
	// Handle time with fixed step and accumulator for variable framerate
	static const float delta_time = 1.0f / 100.0f;

	static sf::Clock clock;
	static float accumulator = 0.0f;
	accumulator += clock.restart().asSeconds();

	while (accumulator >= delta_time) {
		accumulator -= delta_time;

		//// TEST
		entity.update(delta_time);
		//// TEST

		renderer::update(delta_time);
	}
}

void render()
{
	//// TEST
	level::render();
	entity.render();
	//// TEST

	renderer::render();
}

void unload(sf::RenderWindow& window)
{
	renderer::shutdown();
}

int main(void)
{
	// Window
	game_width = sf::VideoMode::getDesktopMode().width;
	game_height = sf::VideoMode::getDesktopMode().height;
	std::cout << "Resolution detected: " <<
		game_width << 'x' <<
		game_height << std::endl;

	sf::RenderWindow window(sf::VideoMode(
		game_width,
		game_height),
		"Sunken");

	// Game loop
	load(window);
	while (window.isOpen()) {
		input(window);
		update();
		render();
	}
	unload(window);
}