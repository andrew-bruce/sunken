#include "cmp_movement.hh"

#include <renderer.hh>
#include <level_loader.hh>

// Class overrides
CmpMovement::CmpMovement(Entity* p) : Component(p), speed_(100.0f) {}

// Move
void CmpMovement::move(const sf::Vector2f& movement)
{
	sf::Vector2f position(parent_->position() + movement);
	if (valid_move(position))
		parent_->move_by(movement);
}

void CmpMovement::move(const float& x, const float& y)
{
	move(sf::Vector2f(x, y));
}

// Whether position is a valid move
bool CmpMovement::valid_move(const sf::Vector2f& position)
{
	// Level bounds checking
	if (level::loaded())
		return level::tile_at(position) != level::Tile::Wall;

	// Get window bounds
	sf::Vector2u size(renderer::window().getSize());

	// Window bounds checking
	return
		position.x >= 0 &&
		position.x <= size.x &&
		position.y >= 0 &&
		position.y <= size.y;
}

