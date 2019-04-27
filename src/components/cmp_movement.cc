#include "cmp_movement.hh"

#include <engine.hh>
#include <level_loader.hh>

// Class overrides
CmpMovement::CmpMovement(Entity* const p)
 : Component(p),
   speed_(level::tile_size() / 2.0f)
{}



// Move
void CmpMovement::move(const sf::Vector2f& movement)
{
	if (valid_move(movement))
		parent_->move_by(movement);
}

void CmpMovement::move(const float& x, const float& y)
{
	move(sf::Vector2f(x, y));
}



// Whether position is a valid move
bool CmpMovement::valid_move(const sf::Vector2f& movement)
{
	auto tile  = level::tile_at(parent_->position() + movement);
	auto tiles = level::tiles_of_type(level::TileType::Solid);

	// If not a solid tile, valid move
	return tiles.find(tile) == tiles.end();
}

