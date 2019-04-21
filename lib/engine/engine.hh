#pragma once

#include <array>
#include <string>

#include <SFML/Graphics.hpp>

#include <maths.hh>
#include <scene.hh>

namespace engine
{
	// Input information
	extern std::array<bool, sf::Keyboard::KeyCount> keyboard;
	extern std::array<bool, sf::Mouse::ButtonCount> mouse;
	extern sf::Vector2f                             mouse_position;
	extern float                                    mouse_wheel_delta;

	// Start engine
	void start(const std::string& title,
	           const unsigned&    width,
	           const unsigned&    height,
	                 Scene*       scene);

	// Window information
	sf::RenderWindow* window();
	sf::Vector2ul window_size();
	void vsync(const bool& b);

	// Change the active scene
	void change_scene(Scene* scene);
};
