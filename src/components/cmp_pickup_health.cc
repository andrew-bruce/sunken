#include "cmp_pickup_health.hh"
#include "cmp_health_player.hh"
#include <iostream>

CmpPickupHealth::CmpPickupHealth(Entity * p)
	: CmpPickup(p), colour_(sf::Color::Red)
{
	auto s = parent_->add_component<CmpShape>();
	s->use_shape<sf::RectangleShape>(sf::Vector2f(12.f, 12.f));
	s->shape().setFillColor(colour_);
}

void CmpPickupHealth::update(const float & delta_time)
{
	CmpPickup::update(delta_time);

	if (picked_up()) {
		// Gets player
		auto player = parent_->scene->entities().find("player").front();

		// Gets it's health component
		auto h = player->compatible_components<CmpHealthPlayer>().front();

		// Increase health
		if (h->health() <= 70)
		{
			h->set_health(h->health() + 30);
		}
		else
		{
			h->set_health(h->health() + 100 - h->health());
		}
	}
}

void CmpPickupHealth::render()
{
}
