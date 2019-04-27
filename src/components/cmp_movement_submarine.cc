#include "cmp_movement_submarine.hh"

#include <algorithm>
#include <array>

#include <level_loader.hh>

#include "cmp_sprite.hh"
#include "../sunken.hh"

// Class overrides
CmpMovementSubmarine::CmpMovementSubmarine(Entity* const p)
: CmpMovement(p),
  state_     (Scanning),
  scan_time_ (2.0f)
{}



// Logic
void CmpMovementSubmarine::update(const float& delta_time)
{

	// Gets parent sprite
	auto s = parent_->compatible_components<CmpSprite>().front();

	// Variables
	const sf::Vector2f movement = direction_ * speed_ * delta_time;
	const sf::Vector2f position = parent_->position();

	// Tile information
	const sf::Vector2ul tile_index  = level::tile_index   (position);
	const level::Tile   tile        = level::tile_at      (tile_index);
	static const auto   water_tiles = level::tiles_of_type(level::TileType::Water);

	switch (state_)
	{
		// Moves in direction while next tile is water and current tile isn't a waypoint
		case Patrol:
		{
			const auto next_tile = level::tile_at(tile_index + sf::Vector2ul(direction_));

			if (water_tiles.find(next_tile) != water_tiles.end()
			 && tile != level::Tile::Waypoint)
			{
				move(movement);
				break;
			}

			target_ = level::tile_position(tile_index);
			state_  = Centering;
		}

		// Move to center of tile
		case Centering:
		{
			// Check direction vector against original vector
			const auto vector = target_ - position;
			const auto d = sf::normalise(vector) * speed_ * delta_time;

			if (sf::length2(d) < sf::length2(vector))
			{
				move(d);
				break;
			}

			move(vector);
			state_ = Scanning;
			scan_time_ = 2.0f;
			break;
		}

		// Scan surroundings (just waits for now)
		case Scanning:
		{
			if (scan_time_ > 0.0f)
			{
				scan_time_ -= delta_time;
				break;
			}

			state_ = Rotating;
		}

		// Find a new direction to travel
		case Rotating:
		{
			static const std::array<sf::Vector2i, 4> directions {{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}};

			// Get all valid directions (water tiles)
			std::vector<sf::Vector2i> all_directions;
			std::copy_if(directions.begin(), directions.end(), std::back_inserter(all_directions),
				[&tile_index](const sf::Vector2i& d)
				{
					const auto tile = level::tile_at(tile_index + sf::Vector2ul(d));
					return water_tiles.find(tile) != water_tiles.end();
				}
			);

			direction_ = sf::Vector2f(all_directions[rand() % all_directions.size()]);
			state_ = Rotated;
		}

		// Move out of waypoint
		case Rotated:
		{
			if (tile != level::Tile::Waypoint)
				state_ = Patrol;
			move(movement);
			break;
		}

		default:
			break;
	}

	if (direction_.x > 0)
	{
		s->sprite().setScale(std::abs(s->sprite().getScale().x), s->sprite().getScale().y);
	}
	else 
	{
		s->sprite().setScale(-std::abs(s->sprite().getScale().x), s->sprite().getScale().y);
	}
}

void CmpMovementSubmarine::render()
{}



// Valid move
bool CmpMovementSubmarine::valid_move(const sf::Vector2f& movement)
{
	const auto tile  = level::tile_at(parent_->position() + movement);
	const auto tiles = level::tiles_of_type(level::TileType::Water);

	// Submarine can only move in water
	return tiles.find(tile) != tiles.end();
}
