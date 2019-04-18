#include "cmp_movement_enemy.hh"

#include <cstdlib>

#include <level_loader.hh>

// Class overrides
CmpMovementEnemy::CmpMovementEnemy(Entity* p)
	: CmpMovement(p), state_(Rotating) 
{
	speed_ = 200.f;
}



// Logic
void CmpMovementEnemy::update(const float& delta_time)
{
	static const sf::Vector2i directions[] {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

	// Variables
	const sf::Vector2f movement     (direction_ * speed_ * delta_time);

	const sf::Vector2f position     (parent_->position());
	const sf::Vector2f new_position (position + movement);

	const sf::Vector2i bad_direction(sf::Vector2i(direction_) * -1);
	      sf::Vector2i new_direction(directions[rand() % 4]);

	switch (state_)
	{
		case Roaming:
		{
			// Move until about to hit a wall or at a waypoint
			if (level::tile_at(position) != level::Tile::Waypoint &&
			    level::tile_at(new_position) != level::Tile::Wall)
			{
				move(movement);
				break;
			}
			else
				state_ = Rotating;
		}

		case Rotating:
		{
			// Current tile index
			sf::Vector2i i(sf::Vector2i(level::tile_index(position)));

			// Get all directions that don't lead immediately to a wall
			std::vector<sf::Vector2i> all_directions;
			for (const sf::Vector2i& d : directions)
				if (level::tile_at(sf::Vector2ul(i + d)) != level::Tile::Wall)
					all_directions.push_back(d);

			// If bigger than 1, remove the bad direction
			if (all_directions.size() > 1)
				all_directions.erase(
					std::find(all_directions.begin(), (all_directions.end()-1),
						bad_direction));
			new_direction = all_directions[rand() % all_directions.size()];

			direction_ = sf::Vector2f(new_direction);
			state_ = Rotated;
		}

		case Rotated:
		{
			// If no longer at waypoint, back to roaming
			if (level::tile_at(position) != level::Tile::Waypoint)
				state_ = Roaming;
			move(movement);
			break;
		}

		default:
		{
			break;
		}
	}
}

void CmpMovementEnemy::render() {}

