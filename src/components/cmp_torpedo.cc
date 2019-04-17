#include "cmp_torpedo.hh"
#include <iostream>

CmpTorpedo::CmpTorpedo(Entity * p, sf::Vector2f direction) : CmpMovement(p), direction_(direction)
{
	speed_ = 150.f;
}

void CmpTorpedo::update(const float & delta_time)
{
	// Normalise movement vector
	direction_ = sf::normalise(direction_);
	direction_ *= speed_ * delta_time;

	// Move player
	move(direction_);

	//
	if (!valid_move(parent_->position() + direction_)) {
		parent_->delete_please();
	}
}

void CmpTorpedo::render()
{
}
