#pragma once

// STD
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

// SFML
#include <SFML/Graphics.hpp>

// PROJECT
#include <maths.hh>



// Level system
class Level
{
public:
	// Tiles and characters to represent them
	enum TILE
	{
		EMPTY = ' ',
		START = 's',
		END = 'e',
		WALL = 'w',
		ENEMY = 'n',
		WAYPOINT = '+'
	};

	// Constructor
	Level() = delete;

	// Whether level has been loaded
	static bool loaded();
	// Unload level
	static void unload();

	// Level dimensions
	static std::size_t width();
	static std::size_t height();
	static float tile_size();

	// Tile at position index
	static TILE tile(const sf::Vector2ul& position);
	// Tile at position
	static TILE tile_at(const sf::Vector2f& position);
	// Position of tile index
	static sf::Vector2f tile_position(const sf::Vector2ul& position);

	// Tile colours
	static sf::Color tile_colour(const TILE& tile);
	static void tile_colour(
		const TILE& tile, 
		const sf::Color& colour);

	// Load level from file
	static void load_level_file(
		const std::string& filepath, 
		const float& tile_size = 100.0f);

	// Render level
	static void render();

protected:

	// Build tile sprites
	static void build_sprites();

	// Level attributes
	static bool loaded_;
	static std::size_t width_;
	static std::size_t height_;
	static float tile_size_;
	static sf::Vector2f offset_;

	// Tile lists
	static std::vector<TILE> tiles_;
	static const std::set<TILE> enum_tile_;
	static std::map<TILE, sf::Color> colours_;
	static std::vector<std::unique_ptr<sf::RectangleShape>> sprites_;
};
