#include "cmp_movement_torpedo.hh"

#include <iostream>

#include <level_loader.hh>

CmpMovementTorpedo::CmpMovementTorpedo(Entity * p, sf::Vector2f direction) : CmpMovement(p), direction_(direction)
{
	speed_ = level::tile_size();
}

void CmpMovementTorpedo::update(const float & delta_time)
{
	// Normalise movement vector
	direction_ = sf::normalise(direction_);
	direction_ *= speed_ * delta_time;

	// Move player
	move(direction_);

	if (!valid_move(direction_))
	{
		parent_->delete_please();
	}
}

void CmpMovementTorpedo::render()
{
}
