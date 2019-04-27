#include "cmp_pickup.hh"
#include "cmp_shape.hh"
#include "cmp_sprite.hh"

#include <iostream>

#include <maths.hh>
#include <scene.hh>

CmpPickup::CmpPickup(Entity* const p)
	: Component(p),
	cooldown_(0.f)
{}

void CmpPickup::pickup()
{
	cooldown_ = 120.f;
}

bool CmpPickup::picked_up() {
	return picked_up_;
}

float CmpPickup::cooldown()
{
	return cooldown_;
}

void CmpPickup::update(const float & delta_time)
{
	if (parent_->scene->entities().find("player").empty())
		return;

	// If it's been picked up, wait for cooldown to respawn
	if (cooldown_ > 0.f)
	{
		cooldown_ -= delta_time;
		picked_up_ = false;
		return;
	}

	// Get player
	auto player = parent_->scene->entities().find("player").front();

	// Gets player and pickup shape components
	auto pls = player->compatible_components<CmpSprite>().front();
	auto ps = parent_->compatible_components<CmpShape>().front();

	// If the player intersects with pickup
	if (pls->sprite().getGlobalBounds().intersects(ps->shape().getGlobalBounds())) {			
		pickup();
		picked_up_ = true;
	}
}
