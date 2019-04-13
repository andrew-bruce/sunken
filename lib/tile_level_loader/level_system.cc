#include "level_system.hh"

#include <fstream>
#include <iostream>

#include <system_renderer.hh>

// Level singleton
namespace level
{
	// Level attributes
	static bool        level_loaded   (false);
	static std::size_t level_width    (0);
	static std::size_t level_height   (0);
	static float       level_tile_size(100.0f);

	// Tile lists
	static std::vector<Tile> level_tiles;
	static const std::set<Tile> level_tile_enums
	{
		Tile::Wall,
		Tile::Start,
		Tile::End,
		Tile::Empty,
		Tile::Waypoint,
		Tile::Enemy
	};
	static std::map<Tile, sf::Color> level_tile_colours
	{
		{
			Tile::Wall,
			sf::Color::White
		},
		{
			Tile::End,
			sf::Color::Red
		}
	};
	static std::vector<std::unique_ptr<sf::RectangleShape>> level_tile_sprites;

	// Build tile sprites
	void build_sprites()
	{
		level_tile_sprites.clear();
		for (std::size_t y(0); y < level_height; ++y)
		{
			for (std::size_t x(0); x < level_width; ++x)
			{
				sf::Vector2ul index(x, y);
				auto s = std::make_unique<sf::RectangleShape>();

				s->setPosition(tile_position(index));
				s->setSize(sf::Vector2f(level_tile_size, level_tile_size));
				s->setFillColor(tile_colour(tile_at(index)));

				level_tile_sprites.push_back(std::move(s));
			}
		}
	}

	// Whether level has been loaded
	bool loaded()
	{
		return level_loaded;
	}

	// Unload level
	void unload()
	{
		level_loaded    = false;
		level_width     = 0;
		level_height    = 0;
		level_tile_size = 0;

		level_tiles.clear();
		level_tile_sprites.clear();
	}

	// Level dimensions
	std::size_t width()
	{
		return level_width;
	}

	std::size_t height()
	{
		return level_height;
	}

	float tile_size()
	{
		return level_tile_size;
	}

	// Tile at position index
	Tile tile_at(const sf::Vector2ul& position)
	{
		if (position.x <= level_width && position.y <= level_height)
			return level_tiles[position.y * level_width + position.x];

		std::cerr <<
			"WARNING"
			" -> LEVEL_SYSTEM"
			" -> GET_TILE"
			" -> OUT OF BOUNDS: "
			<< position.x << ", " << position.y << std::endl;

		return Tile::Empty;
	}

	// Tile at position
	Tile tile_at(const sf::Vector2f& position)
	{
		if (position.x >= 0 && position.y >= 0)
			return tile_at(sf::Vector2ul(position / level_tile_size));

		std::cerr <<
			"WARNING"
			" -> LEVEL_SYSTEM"
			" -> GET_TILE_AT"
			" -> OUT OF BOUNDS: "
			<< position.x << ", " << position.y << std::endl;

		return Tile::Empty;
	}

	// Position of tile index
	sf::Vector2f tile_position(const sf::Vector2ul& index)
	{
		return sf::Vector2f(index) * level_tile_size;
	}

	// Index of tile at position
	sf::Vector2ul tile_index(const sf::Vector2f& position)
	{
		return sf::Vector2ul(position / level_tile_size);
	}

	// Get indices of tiles
	std::vector<sf::Vector2ul> find_tiles(const Tile& tile)
	{
		std::vector<sf::Vector2ul> output;

		for (std::size_t x(0); x < level_width; ++x)
			for (std::size_t y(0); y < level_height; ++y)
				if (tile == tile_at(sf::Vector2ul(x, y)))
					output.emplace_back(x, y);

		return std::move(output);
	}

	// Tile colours
	sf::Color tile_colour(const Tile& tile)
	{
		if (level_tile_colours.find(tile) == level_tile_colours.end())
			level_tile_colours[tile] = sf::Color::Transparent;

		return level_tile_colours[tile];
	}

	void tile_colour(const Tile& tile, const sf::Color& colour)
	{
		level_tile_colours[tile] = colour;
	}

	// Load level from file
	void load_level_file(const std::string& filepath, const float& tile_size)
	{
		// Set variables
		level_tile_size = tile_size;
		level_height    = 0;
		level_width     = 0;

		// Read file to string
		std::string content;
		{
			std::ifstream file(filepath);
			if (!file.good())
			{
				std::cerr <<
					"ERROR"
					" -> LEVEL_SYSTEM"
					" -> LOAD_LEVEL_FILE"
					" -> FILE ERROR: "
					<< filepath << std::endl;

				return unload();
			}

			content.append(std::istreambuf_iterator<char>(file), {});
		}

		// Populate temporary vector with contents of string
		std::vector<Tile> temp_tiles;
		for (std::size_t i(0); i < content.size(); ++i)
		{
			// Next character
			const char c(content[i]);

			// New line
			if (c == '\n')
			{
				if (!level_width)
					level_width = i;
				++level_height;
				continue;
			}

			// If character matches tile
			bool invalid(true);
			for (const Tile& tile : level_tile_enums)
				if (tile == c)
				{
					temp_tiles.push_back(tile);
					invalid = false;
					break;
				}

			// Invalid character
			if (invalid)
				std::cerr <<
					"WARNING"
					" -> LEVEL_SYSTEM"
					" -> LOAD_LEVEL_FILE"
					" -> INVALID CHARACTER: "
					<< c << std::endl;
		}

		// Invalid amount of tiles
		if (temp_tiles.size() != level_width * level_height)
		{
			std::cerr <<
				"ERROR"
				" -> LEVEL_SYSTEM"
				" -> LOAD_LEVEL_FILE"
				" -> INVALID TILE COUNT: "
				<< filepath << std::endl;

			return unload();
		}

		// Needs start and end tiles
		if (find_tiles(Tile::Start).size() == 0)
		{
			std::cerr <<
				"ERROR -> "
				"LEVEL_SYSTEM -> "
				"LOAD_LEVEL_FILE -> "
				"NO START TILES"
				<< std::endl;

			return unload();
		}

		if (find_tiles(Tile::End).size() == 0)
		{
			std::cerr <<
				"ERROR -> "
				"LEVEL_SYSTEM -> "
				"LOAD_LEVEL_FILE -> "
				"NO END TILES"
				<< std::endl;

			return unload();
		}

		// Moves tiles and build sprites
		level_tiles.swap(temp_tiles);
		build_sprites();

		// Level is loaded
		level_loaded = true;
		std::cout <<
			"SUCCESS"
			" -> LEVEL_SYSTEM"
			" -> LOAD_LEVEL_FILE: "
			<< "Width = " << level_width << ", "
			<< "Height = " << level_height << ", "
			<< "File = " << filepath << std::endl;
	}

	// Render level
	void render()
	{
		for (std::size_t i(0); i < level_width * level_height; ++i)
			renderer::queue(level_tile_sprites[i].get());
	}
};

