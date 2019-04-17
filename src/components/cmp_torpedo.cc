#include "cmp_torpedo.hh"
#include <iostream>

CmpTorpedo::CmpTorpedo(Entity * p) : CmpMovement(p)
{
	speed_ = 150.f;
}

void CmpTorpedo::update(const float & delta_time)
{
	// Input decides direction vector
	sf::Vector2f movement(1.f, 0.0f);

	// Normalise movement vector
	movement = sf::normalise(movement);
	movement *= speed_ * delta_time;

	// Move player
	move(movement);

	if (!valid_move(parent_->position()+movement)) {
		parent_->delete_please();
		std::cout << "WALL" << std::endl;
	}
}

void CmpTorpedo::render()
{
}
