#include "cmp_pickup_ammo.hh"
#include "cmp_combat.hh"
#include <iostream>

CmpPickupAmmo::CmpPickupAmmo(Entity * p)
	: CmpPickup(p), colour_(sf::Color::Cyan)
{
	auto s = parent_->add_component<CmpShape>();
	s->use_shape<sf::RectangleShape>(sf::Vector2f(12.f, 12.f));
	s->shape().setFillColor(colour_);
}

void CmpPickupAmmo::update(const float & delta_time)
{
	CmpPickup::update(delta_time);
	if (distance() <= 10)
	{
		// Gets player
		auto player = parent_->scene->entities().find("player").front();

		// Gets it's combat component
		auto c = player->compatible_components<CmpCombat>().front();

		// Increase ammo
		c->pickup_ammo(5);
	}		
}

void CmpPickupAmmo::render(){}
