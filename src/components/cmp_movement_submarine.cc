#include "cmp_movement_submarine.hh"

#include <level_loader.hh>

// Class overrides
CmpMovementSubmarine::CmpMovementSubmarine(Entity* const p)
: CmpMovement(p)
{}



// Logic
void CmpMovementSubmarine::update(const float& delta_time)
{}

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
