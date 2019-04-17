#pragma once

#include <array>
#include <string>

#include <SFML/Graphics.hpp>

#include <maths.hh>
#include <scene.hh>

namespace engine
{
	extern std::array<bool, sf::Keyboard::KeyCount> keyboard;
	extern std::array<bool, sf::Mouse::ButtonCount> mouse;

	void start(unsigned width,
	           unsigned height,
	           const std::string& title,
	           Scene* scene);

	sf::RenderWindow& window();
	sf::Vector2ul window_size();

	void vsync(bool b);

	void change_scene(Scene* scene);
};
