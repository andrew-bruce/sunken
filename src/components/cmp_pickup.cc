#include "cmp_pickup.hh"
#include "cmp_shape.hh"
#include "cmp_sprite.hh"

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

bool CmpPickup::picked_up() {
	return picked_up_;
}

void CmpPickup::update(const float & delta_time)
{
	if (parent_->scene->entities().find("player").empty())
		return;

	// Get player
	auto player = parent_->scene->entities().find("player").front();

	// Gets player and pickup shape components
	auto pls = player->compatible_components<CmpSprite>().front();
	auto ps = parent_->compatible_components<CmpShape>().front();

	// If the player intersects with pickup
	if (pls->sprite().getGlobalBounds().intersects(ps->shape().getGlobalBounds())) {
		parent_->delete_please();
		picked_up_ = true;
		pickup();
	}
}
