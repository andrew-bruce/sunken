#include "cmp_pickup_ammo.hh"

CmpPickupAmmo::CmpPickupAmmo(Entity * p)
	: CmpPickup(p), colour_(sf::Color::Cyan)
{
	auto s = parent_->add_component<CmpShape>();
	s->use_shape<sf::RectangleShape>(sf::Vector2f(12.f, 12.f));
	s->shape().setFillColor(colour_);
}

void CmpPickupAmmo::update(const float & delta_time)
{
}

void CmpPickupAmmo::render()
{
}
