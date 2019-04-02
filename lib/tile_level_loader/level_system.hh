#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

// SFML
#include <SFML/Graphics.hpp>

// PROJECT
#include <maths.hh>


namespace level
{
	enum Tile
	{
		Empty    = ' ',
		Start    = 's',
		End      = 'e',
		Wall     = 'w',
		Enemy    = 'n',
		Waypoint = '+'
	};

	bool loaded();
	void unload();

	// Level dimensions
	std::size_t width();
	std::size_t height();
	float       tile_size();

	// Tile at position index
	Tile tile_at(const sf::Vector2ul& position);
	// Tile at position
	Tile tile_at(const sf::Vector2f& position);
	// Position of tile index
	sf::Vector2f tile_position(const sf::Vector2ul& index);
	// Index of tile at position
	sf::Vector2ul tile_index(const sf::Vector2f& position);
	// Get indices of tiles
	std::vector<sf::Vector2ul> find_tiles(const Tile& tile);

	// Tile colours
	sf::Color tile_colour(const Tile& tile);
	void      tile_colour(const Tile& tile, const sf::Color& colour);

	// Load level from file
	void load_level_file(
		const std::string& filepath,
		const float& tile_size = 100.0f);

	// Render level
	void render();
};

