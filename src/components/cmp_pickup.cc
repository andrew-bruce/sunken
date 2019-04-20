#include "cmp_pickup.hh"
#include "cmp_shape.hh"
#include <maths.hh>
#include <iostream>

CmpPickup::CmpPickup(Entity * p) : Component(p)
{
}

void CmpPickup::pickup()
{
	parent_->delete_please();
}

bool CmpPickup::picked_up() {
	return picked_up_;
}

void CmpPickup::update(const float & delta_time)
{
	// Get player
	auto player = parent_->scene->entities().find("player").front();

	// Gets player and pickup's shape component
	auto pls = player->compatible_components<CmpShape>().front();
	auto ps = parent_->compatible_components<CmpShape>().front();

	// If the player intersects with pickup
	if (pls->shape().getGlobalBounds().intersects(ps->shape().getGlobalBounds())) {
		parent_->delete_please();
		picked_up_ = true;
		pickup();
	}
}
