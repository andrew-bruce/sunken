#include "level_loader.hh"

#include <fstream>
#include <iostream>

#include <system_renderer.hh>

// Level singleton
namespace level
{
	// Level attributes
	static bool          loaded_    = false;
	static float         tile_size_ = 100.0f;
	static sf::Vector2ul size_      = {0, 0};

	// Tile lists
	static std::vector<Tile> tiles_;
	static const std::set<Tile> tile_enums_ =
	{
		Tile::Empty,
		Tile::Start,
		Tile::End,
		Tile::Wall,
		Tile::Enemy,
		Tile::Waypoint
	};
	static std::map<Tile, sf::Color> tile_colours_
	{
		{ Tile::End,  sf::Color::Red },
		{ Tile::Wall, sf::Color::White }
	};
	static std::vector<std::unique_ptr<sf::RectangleShape>> tile_sprites_;



	void build_sprites(bool optimise = true)
	{
		tile_sprites_.clear();

		// Tile properties used for sprites
		struct tile_def
		{
			sf::Vector2f p;
			sf::Vector2f s;
			sf::Color c;
		};

		std::vector<tile_def> tiles;
		const sf::Vector2f size(tile_size_, tile_size_);

		// Populate tiles list with properties
		for (std::size_t y = 0; y < size_.y; ++y)
			for (std::size_t x = 0; x < size_.x; ++x)
			{
				Tile t(tile_at(sf::Vector2ul(x, y)));
				if (t == Tile::Empty)
					continue;

				tile_def td;
				td.p = tile_position({x, y});
				td.s = size;
				td.c = tile_colour(t);
				tiles.push_back(td);
			}

		// Optimisation
		if (optimise && tiles.size() > 0)
		{
			tile_def last = tiles.front();
			std::size_t same_count;

			// Combine tiles in X direction
			std::vector<tile_def> tox;
			for (std::size_t i = 1; i < tiles.size(); ++i)
			{
				/*
				Height is the same
				Width matches with the current same_count
				Colour is the same
				*/
				bool is_same = tiles[i].p.y == last.p.y
				         && tiles[i].p.x == last.p.x + size.x * (same_count + 1)
					     && tiles[i].c   == last.c;
				if (is_same)
					++same_count;
				else
				{
					if (same_count)
						last.s.x = size.x * (same_count + 1);
					tox.push_back(last);
					same_count = 0;
					last = tiles[i];
				}
			}

			// Catch last tile
			if (same_count > 0)
			{
				last.s.x = size.x * (same_count + 1);
				tox.push_back(last);
				same_count = 0;
			}

			// Combine tiles in Y direction
			std::vector<tile_def> toy;
			for (std::size_t i = 0; i < tox.size(); ++i)
			{
				last = tox[i];
				for (std::size_t j = i + 1; j < tox.size(); ++j)
				{
					/*
					Width is the same
					Size is the same
					Height matches with the current same_count
					Colour is the same
					*/
					bool same = tox[j].p.x == last.p.x
					         && tox[j].s   == last.s
							 && tox[j].p.y == last.p.y + size.y * (same_count + 1)
							 && tox[j].c   == last.c;
					if (same)
					{
						++same_count;
						tox.erase(tox.begin() + j--);
					}
				}

				if (same_count)
					last.s.y = size.y * (same_count + 1);
				toy.push_back(last);
				same_count = 0;
			}

			tiles.swap(toy);
		}

		for (const tile_def& t : tiles)
		{
			auto s = std::make_unique<sf::RectangleShape>();

			s->setPosition(t.p);
			s->setSize(t.s);
			s->setFillColor(t.c);

			tile_sprites_.push_back(std::move(s));
		}

		std::cout
			<< "INFO Level with " << size_.x * size_.y
			<< " tiles using " << tile_sprites_.size()
			<< " sprites" << std::endl;
	}



	// Loading
	void load(const std::string& filepath, const float& tile_size)
	{
		// Set variables
		tile_size_ = tile_size;
		size_ = {0, 0};

		// Read file to string
		std::string file_content;
		{
			std::ifstream file(filepath);
			if (!file.good())
			{
				std::cerr << "ERROR loading level " << filepath << std::endl;
				return unload();
			}
			file_content.append(std::istreambuf_iterator<char>(file), {});
		}

		// Populate temporary vector with contents of string
		std::vector<Tile> tiles;
		for (std::size_t i = 0; i < file_content.size(); ++i)
		{
			const Tile t = static_cast<Tile>(file_content[i]);

			if (t == '\n')
			{
				if (size_.x == 0)
					size_.x = i;
				++size_.y;
				continue;
			}

			if (tile_enums_.find(t) != tile_enums_.end())
				tiles.push_back(t);
			else
				std::cerr << "WARNING level contains invalid tile: " << t << std::endl;
		}

		// Invalid amount of tiles
		if (tiles.size() != size_.x * size_.y)
		{
			std::cerr << "ERROR tile count doesn't match size of " << filepath << std::endl;
			return unload();
		}

		// Need start and end tiles
		if (std::find(tiles.begin(), tiles.end(), Tile::Start) == tiles.end())
		{
			std::cerr << "ERROR no start tile in level " << filepath << std::endl;
			return unload();
		}

		if (std::find(tiles.begin(), tiles.end(), Tile::End) == tiles.end())
		{
			std::cerr << "ERROR no end tile in level " << filepath << std::endl;
			return unload();
		}

		// Move tiles from temporary storage
		tiles_.swap(tiles);

		// Moves tiles and build sprites
		build_sprites();

		// Level is loaded
		loaded_ = true;
		std::cout
			<< "INFO level loaded: " << filepath
			<< ", dimensions:" << size_ << std::endl;
	}

	void unload()
	{
		loaded_    = false;
		size_      = {0, 0};
		tile_size_ = 0;

		tiles_.clear();
		tile_sprites_.clear();
	}



	bool loaded()
	{
		return loaded_;
	}

	float tile_size()
	{
		return tile_size_;
	}

	std::size_t width()
	{
		return size_.x;
	}

	std::size_t height()
	{
		return size_.y;
	}



	// Render level
	void render()
	{
		for (const std::unique_ptr<sf::RectangleShape>& s : tile_sprites_)
			renderer::queue(s.get());
	}



	// Tile at position/index
	Tile tile_at(const sf::Vector2f& position)
	{
		if (position.x >= 0 && position.y >= 0)
			return tile_at(tile_index(position));

		std::cerr << "WARNING invalid level position " << position << std::endl;
		return Tile::Empty;
	}

	Tile tile_at(const sf::Vector2ul& index)
	{
		if (index.x <= size_.x && index.y <= size_.y)
			return tiles_[index.y * size_.x + index.x];

		std::cerr << "WARNING invalid level index " << index << std::endl;
		return Tile::Empty;
	}

	// Return indices of all tiles matching search
	std::vector<sf::Vector2ul> find_tiles(const Tile& tile)
	{
		std::vector<sf::Vector2ul> output;
		for (std::size_t x = 0; x < size_.x; ++x)
			for (std::size_t y = 0; y < size_.y; ++y)
				if (tile == tile_at(sf::Vector2ul(x, y)))
					output.emplace_back(x, y);
		return std::move(output);
	}



	// Tile colours
	sf::Color tile_colour(const Tile& tile)
	{
		if (tile_colours_.find(tile) == tile_colours_.end())
			tile_colours_[tile] = sf::Color::Transparent;
		return tile_colours_[tile];
	}

	void tile_colour(const Tile& tile, const sf::Color& colour)
	{
		tile_colours_[tile] = colour;
	}



	// Position of tile index
	sf::Vector2f tile_position(const sf::Vector2ul& index)
	{
		return sf::Vector2f(index) * tile_size_;
	}

	// Index of tile at position
	sf::Vector2ul tile_index(const sf::Vector2f& position)
	{
		return sf::Vector2ul(position / tile_size_);
	}
};
