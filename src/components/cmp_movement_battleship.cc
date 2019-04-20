#include "cmp_movement_battleship.hh"

#include <level_loader.hh>

// Class overrides
CmpMovementBattleship::CmpMovementBattleship(Entity* const p)
: CmpMovement(p)
{}



// Logic
void CmpMovementBattleship::update(const float& delta_time)
{}

void CmpMovementBattleship::render()
{}



// Valid move
bool CmpMovementBattleship::valid_move(const sf::Vector2f& movement)
{
	auto tile  = level::tile_at(parent_->position() + movement);
	auto tiles = level::tiles_of_type(level::TileType::Air);

	// Battleship can only move in air
	return tiles.find(tile) != tiles.end();
}
