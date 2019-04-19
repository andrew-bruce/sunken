#include "cmp_movement_torpedo.hh"
#include "cmp_shape.hh"

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

	// Gets torpedo tag
	std::set<std::string>::iterator it = parent_->tags().begin();
	std::advance(it, 0);
	std::string tag = *it;

	// Enemy torpedo collision
	if (tag == "enemy_torpedo")
	{
		// Gets player
		auto player = parent_->scene->entities().find("player").front();

		// Gets it's shape component
		auto ps = player->compatible_components<CmpShape>().front();
		auto ts = parent_->compatible_components<CmpShape>().front();

		// If the enemy torpedo colides with the player
		if (ps->shape().getGlobalBounds().intersects(ts->shape().getGlobalBounds())) {
			parent_->delete_please();
			std::cout << "HIT" << std::endl;
		}
	} 
	else if (tag == "player_torpedo")
	{
		// Deal with player torpedo collision
	}
}

void CmpMovementTorpedo::render()
{
}
