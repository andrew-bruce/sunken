#include "cmp_pickup.hh"

#include <iostream>

#include <maths.hh>
#include <scene.hh>

CmpPickup::CmpPickup(Entity* const p)
: Component(p)
{}

void CmpPickup::pickup()
{
	parent_->delete_please();
}

float CmpPickup::distance()
{
	return distance_;
}

void CmpPickup::update(const float & delta_time)
{
	// Get player
	auto player = parent_->scene->entities().find("player").front();

	// Get player and enemy position
	sf::Vector2f player_p= player->position();
	sf::Vector2f pickup_p = parent_->position();

	// Get distance between enemy and player
	distance_ = sf::length(player->position() - parent_->position());

	// If the enemy is close enough to the player, fire in their direction
	if (distance_ <= 10)
	{
		pickup();
	}
}
