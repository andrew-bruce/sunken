#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include <maths.hh>

namespace level
{
	enum Tile
	{
		Empty      = '\0',
		Player     = '@',
		Water      = '.',
		Air        = '~',
		Wall       = '#',
		Health     = '+',
		Ammo       = '=',
		Waypoint   = '*',
		Objective  = '!',
		Battleship = 'B',
		Submarine  = 'S',
		EnemySpawn = 'E'
	};

	// Loading
	void load(const std::string& filepath, const float& tile_size = 100.0f);
	void unload();

	// Level information
	bool        loaded();
	float       tile_size();
	std::size_t width();
	std::size_t height();

	// Render level
	void render();

	// Tile at position/index
	Tile tile_at(const sf::Vector2f& position);
	Tile tile_at(const sf::Vector2ul& position);
	std::vector<sf::Vector2ul> find_tiles(const Tile& tile);

	// Tile colours
	sf::Color tile_colour(const Tile& tile);
	void      tile_colour(const Tile& tile, const sf::Color& colour);

	// Convert between position and index
	sf::Vector2f tile_position(const sf::Vector2ul& index);
	sf::Vector2ul tile_index(const sf::Vector2f& position);
};

