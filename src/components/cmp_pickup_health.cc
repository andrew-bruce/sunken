#include "cmp_pickup_health.hh"

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
}

void CmpPickupHealth::render()
{
}
