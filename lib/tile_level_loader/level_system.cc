#include "level_system.hh"



// STD
#include <fstream>
#include <iostream>

// PROJECT
#include <system_renderer.hh>



// Whether level has been loaded
bool Level::loaded()
{
	return loaded_;
}

// Unload level
void Level::unload()
{
	loaded_ = false;
	width_ = 0;
	height_ = 0;
	tile_size_ = 0;
	offset_ = sf::Vector2f(0.0f, 0.0f);

	tiles_.clear();
	sprites_.clear();
}



// Level dimensions
std::size_t Level::width()
{
	return width_;
}

std::size_t Level::height()
{
	return height_;
}

float Level::tile_size()
{
	return tile_size_;
}



// Tile at position index
Level::TILE Level::tile(const sf::Vector2ul& position)
{
	if (position.x <= width_ && position.y <= height_)
		return tiles_[position.y * width_ + position.x];

	std::cerr <<
		"ERROR -> LEVEL_SYSTEM -> GET_TILE -> OUT OF BOUNDS: " <<
		position.x << ", " <<
		position.y << std::endl;

	return EMPTY;
}

// Tile at position
Level::TILE Level::tile_at(const sf::Vector2f& position)
{
	const sf::Vector2f p = position - offset_;
	if (p.x >= 0 && p.y >= 0)
		return tile(sf::Vector2ul(p / tile_size_));

	std::cerr <<
		"ERROR -> LEVEL_SYSTEM -> GET_TILE_AT -> OUT OF BOUNDS: " <<
		position.x << ", " <<
		position.y << std::endl;

	return EMPTY;
}

// Position of tile index
sf::Vector2f Level::tile_position(const sf::Vector2ul& position)
{
	return sf::Vector2f(position) * tile_size_;
}



// Tile colours
sf::Color Level::tile_colour(const TILE& tile)
{
	if (colours_.find(tile) == colours_.end())
		colours_[tile] = sf::Color::Transparent;

	return colours_[tile];
}

void Level::tile_colour(
	const TILE& tile,
	const sf::Color& colour)
{
	colours_[tile] = colour;
}



// Load level from file
void Level::load_level_file(
	const std::string& filepath,
	const float& tile_size)
{
	// Set variables
	tile_size_ = tile_size;
	std::size_t height(0);
	std::size_t width(0);

	// Read file to string
	std::string content;
	{
		std::ifstream file(filepath);
		if (!file.good())
		{
			std::cerr <<
				"ERROR -> LEVELSYSTEM -> LOAD_LEVEL_FILE -> FILE ERROR: " <<
				filepath << std::endl;

			return unload();
		}

		content.append(std::istreambuf_iterator<char>(file), {});
	}

	// Populate temporary vector with contents of string
	std::vector<TILE> temp_tiles;
	for (std::size_t i(0); i < content.size(); ++i)
	{
		// Next character
		const char c(content[i]);

		// New line
		if (c == '\n')
		{
			if (!width)
				width = i;
			++height;
		}
		else
		{
			// If character matches tile
			bool invalid(true);
			for (const TILE& tile : enum_tile_)
				if (tile == c)
				{
					temp_tiles.push_back(tile);
					invalid = false;
				}

			// Invalid character
			if (invalid)
				std::cerr <<
				"WARNING -> LEVELSYSTEM -> LOAD_LEVEL_FILE -> INVALID CHARACTER: " <<
				c << std::endl;
		}
	}

	// Invalid amount of tiles
	if (temp_tiles.size() != width * height)
	{
		std::cerr <<
			"ERROR -> LEVELSYSTEM -> LOAD_LEVEL_FILE -> INVALID TILE COUNT: " <<
			filepath << std::endl;

		return unload();
	}

	// Set values
	width_ = width;
	height_ = height;

	tiles_.swap(temp_tiles);

	build_sprites();

	std::cout <<
		"SUCCESS -> LEVELSYSTEM -> LOAD_LEVEL_FILE: Width = " <<
		width_ << ", Height = " <<
		height_ << ", File = " <<
		filepath << std::endl;

	loaded_ = true;
}



// Render level
void Level::render()
{
	for (std::size_t i(0); i < width_ * height_; ++i)
		Renderer::queue(sprites_[i].get());
}



// Build tile sprites
void Level::build_sprites()
{
	sprites_.clear();
	for (std::size_t y(0); y < height_; ++y)
	{
		for (std::size_t x(0); x < width_; ++x)
		{
			auto s =
				std::make_unique<sf::RectangleShape>();

			s->setPosition(
				tile_position(sf::Vector2ul(
					x,
					y)));

			s->setSize(sf::Vector2f(
				tile_size_,
				tile_size_));

			s->setFillColor(
				tile_colour(tile(sf::Vector2ul(
					x,
					y))));

			sprites_.push_back(std::move(s));
		}
	}
}



// Level attributes
bool Level::loaded_ = false;
std::size_t Level::width_;
std::size_t Level::height_;
float Level::tile_size_(100.0f);
sf::Vector2f Level::offset_(0.0f, 0.0f);



// Tile lists
std::vector<Level::TILE> Level::tiles_;
const std::set<Level::TILE> Level::enum_tile_
{
	WALL,
	START,
	END,
	EMPTY,
	WAYPOINT,
	ENEMY
};
std::map<Level::TILE, sf::Color> Level::colours_
{
	{
		WALL,
		sf::Color::White
	}, {
		END,
		sf::Color::Red
	}
};
std::vector<std::unique_ptr<sf::RectangleShape>> Level::sprites_;
