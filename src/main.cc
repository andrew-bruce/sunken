#include <array>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>

#include <physics.hh>
#include <system_renderer.hh>
#include <level_system.hh>
#include <ecm.hh>
#include <cmp_shape.hh>

#include "cmp_movement_player.hh"
#include "cmp_movement_enemy.hh"
#include "cmp_combat_player.hh"
#include "sunken.hh"

// Window
std::size_t game_width;
std::size_t game_height;

// Keyboard
std::array<bool, sf::Keyboard::KeyCount> keyboard;

//// TEST
std::vector<std::unique_ptr<sf::RectangleShape>> shapes;

Entity player;
//// TEST //

void reset() {}

void load(sf::RenderWindow& window)
{
	srand(time(NULL));

	std::cout << "Initialising renderer..." << std::endl;
	renderer::initialise(window);

	std::cout << "Loading font..." << std::endl;
	font.loadFromFile("res/fonts/FiraCode-Regular.ttf");

	//// TEST
	// World
	const b2Vec2 gravity(0.0f, -9.8f);
	physics::initialise(new b2World(gravity));

	//// TEST
	// Loads items to the screen at game beginning
	//level::load_level_file("res/levels/maze2.txt");

	auto s = player.add_component<CmpShape>();
	s->use_shape<sf::CircleShape>(12.f);
	s->shape().setFillColor(sf::Color::Yellow);
	s->shape().setOrigin(sf::Vector2f(12.f, 12.f));

	auto m = player.add_component<CmpMovementPlayer>();
	auto c = player.add_component<CmpCombatPlayer>();


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
	static const float delta_time(1.0f / 100.0f);

	static sf::Clock clock;
	static float accumulator(0.0f);
	accumulator += clock.restart().asSeconds();

	while (accumulator >= delta_time) {
		accumulator -= delta_time;

		//// TEST
		physics::update(delta_time);
		std::vector<b2Body*> bodies = physics::bodies();
		for (int i = 0; i < bodies.size(); ++i)
		{
			shapes[i]->setPosition(physics::invert_height(physics::bv2_to_sv2(bodies[i]->GetPosition()), game_height));

			shapes[i]->setRotation((180 / b2_pi) * bodies[i]->GetAngle());
		}
		//// TEST

		renderer::update(delta_time);
	}

	player.update(delta_time);
}

void render()
{
	//// TEST
	level::render();
	for (auto& s : shapes)
		renderer::queue(s.get());
	//// TEST

	renderer::render();
	player.render();
}

void unload(sf::RenderWindow& window)
{
	physics::cleanup();
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
