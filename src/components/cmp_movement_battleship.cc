#include "cmp_movement_battleship.hh"


#include <scene.hh>
#include <level_loader.hh>
#include <iostream>

// Class overrides
CmpMovementBattleship::CmpMovementBattleship(Entity* const p)
: CmpMovement(p)
{
	// Battleships move slowly
	speed_ = 5.f;
}



// Logic
void CmpMovementBattleship::update(const float& delta_time)
{
	// Gets player
	auto player = parent_->scene->entities().find("player").front();

	// Booleans to store whether the battleship is going to hit another one or not
	bool ship_collision_right = false;
	bool ship_collision_left = false;

	// Loops through other ships
	std::vector<Entity*> other_ships = parent_->scene->entities().find("battleship");
	for (auto bs : other_ships)
	{
		// Doesn't check itself
		if (bs != parent_) {
			// Difference between current ship and other ships x pos
			float x_diff = bs->position().x - parent_->position().x;

			// Sets left and right collision when ships come close
			if (x_diff >= 0 && x_diff <= 100)
				ship_collision_right = true;
			else if (x_diff <= 0 && x_diff >= -100)
				ship_collision_left = true;
		}
	}


	// Ship only moves toward player if it's not too far away
	float player_x_diff = player->position().x - parent_->position().x;

	// Matches player x axis movement as long as another ship isn't nearby
	sf::Vector2f movement;
	if (player->position().x >= parent_->position().x && !ship_collision_right && player_x_diff >= 0 && player_x_diff <= 200) 
	{
		movement.x = 1.f;
	}
	else if(player->position().x <= parent_->position().x && !ship_collision_left && player_x_diff <= 0 && player_x_diff >= -200)
	{
		movement.x = -1.f;
	}

	// Normalise movement vector
	movement = sf::normalise(movement);
	movement *= speed_ * delta_time;

	// Move player
	move(movement);
}

void CmpMovementBattleship::render()
{}



// Valid move
bool CmpMovementBattleship::valid_move(const sf::Vector2f& movement)
{
	const auto tile  = level::tile_at(parent_->position() + movement);
	const auto tiles = level::tiles_of_type(level::TileType::Air);

	// Battleship can only move in air
	return tiles.find(tile) != tiles.end();
}
