#pragma once

#include <array>

#include <SFML/Graphics.hpp>

// Window
extern std::size_t game_width;
extern std::size_t game_height;

// Keyboard
extern std::array<bool, sf::Keyboard::KeyCount> keyboard;

// Font
extern sf::Font font;

