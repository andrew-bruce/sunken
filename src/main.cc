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
#include "sunken.hh"

// Window
std::size_t game_width;
std::size_t game_height;

// Keyboard
std::array<bool, sf::Keyboard::KeyCount> keyboard;

//// TEST
b2World* world;
std::vector<b2Body*> bodies;
std::vector<std::unique_ptr<sf::RectangleShape>> shapes;
//// TEST

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
	world = new b2World(gravity);
	physics::initialise(world);

	// Walls
	sf::Vector2f walls[] {
		// Top
		sf::Vector2f(game_width / 2.0f, 5.0f),
		sf::Vector2f(game_width, 10.0f),
		// Bottom
		sf::Vector2f(game_width / 2.0f, game_height - 5.0f),
		sf::Vector2f(game_width, 10.0f),
		// Left
		sf::Vector2f(5.0f, game_height / 2.0f),
		sf::Vector2f(10.0f, game_height),
		// Right
		sf::Vector2f(game_width - 5.0f, game_height / 2.0f),
		sf::Vector2f(10.0f, game_height)
	};
	for (int i = 0; i < 4; ++i)
	{
		auto s = std::make_unique<sf::RectangleShape>();
		s->setSize(walls[2 * i + 1]);
		s->setOrigin(walls[2 * i + 1] / 2.0f);
		s->setPosition(walls[2 * i]);
		shapes.push_back(std::move(s));

		auto b = physics::create_box(false, *shapes.back());
		bodies.push_back(b);
	}

	// Boxes
	for (int i(1); i < 11; ++i)
	{
		// Shapes
		auto s = std::make_unique<sf::RectangleShape>();
		s->setPosition(i * (game_width / 12.0f), game_height * 0.7f);
		s->setSize(sf::Vector2f(50.0f, 50.0f));
		s->setOrigin(25.0f, 25.0f);
		s->setFillColor(sf::Color::White);
		shapes.push_back(std::move(s));

		// Physics
		auto b = physics::create_box(true, *shapes.back());
		b->ApplyAngularImpulse(5.0f, true);
		bodies.push_back(b);
	}
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
	static const float delta_time(1.0f / 100.0f);

	static sf::Clock clock;
	static float accumulator(0.0f);
	accumulator += clock.restart().asSeconds();

	while (accumulator >= delta_time) {
		accumulator -= delta_time;

		//// TEST
		physics::update(delta_time);
		for (int i = 0; i < bodies.size(); ++i)
		{
			shapes[i]->setPosition(physics::invert_height(physics::bv2_to_sv2(bodies[i]->GetPosition()), game_height));

			shapes[i]->setRotation((180 / b2_pi) * bodies[i]->GetAngle());
		}
		//// TEST

		renderer::update(delta_time);
	}
}

void render()
{
	//// TEST
	level::render();
	for (auto& s : shapes)
		renderer::queue(s.get());
	//// TEST

	renderer::render();
}

void unload(sf::RenderWindow& window)
{
	for (auto& b : bodies)
		world->DestroyBody(b);
	delete world;
	bodies.clear();
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
