#include "cmp_movement.hh"

#include <system_renderer.hh>
#include <level_system.hh>



CmpMovement::CmpMovement(Entity* p)
: Component(p), speed_(100.0f) {}



// Move
void CmpMovement::move(const sf::Vector2f& movement)
{
	sf::Vector2f position(parent_->position() + movement);
	if (valid_move(position))
		parent_->move_by(movement);
}

void CmpMovement::move(const float& x, const float& y)
{
	sf::Vector2f movement(x, y);
	move(movement);
}



// Whether position is a valid move
bool CmpMovement::valid_move(sf::Vector2f& position)
{
	// Get window bounds
	sf::Vector2u size(renderer::window().getSize());

	// Window bounds checking
	bool bounds(
		position.x >= 0 &&
		position.x <= size.x &&
		position.y >= 0 &&
		position.y <= size.y);

	// Level bounds checking
	if (bounds && Level::loaded())
		bounds = bounds &&
			Level::WALL != Level::tile_at(
				position);

	return bounds;
}
