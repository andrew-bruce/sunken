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

	// Matches player x axis movement
	sf::Vector2f movement;
	if (player->position().x >= parent_->position().x) 
	{
		movement.x = 1.f;
	}
	else
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
