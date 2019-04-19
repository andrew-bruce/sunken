#include "cmp_pickup_health.hh"

#include <level_loader.hh>

#include "cmp_shape.hh"

CmpPickupHealth::CmpPickupHealth(Entity* const p)
: CmpPickup(p),
  colour_(sf::Color::Red)
{
	auto size = sf::Vector2f(level::tile_size(), level::tile_size()) / 16.0f;
	auto s = parent_->add_component<CmpShape>();
	s->use_shape<sf::RectangleShape>(size);
	s->shape().setOrigin(size / 2.0f);
	s->shape().setFillColor(colour_);
}

void CmpPickupHealth::update(const float & delta_time)
{
	CmpPickup::update(delta_time);
}

void CmpPickupHealth::render()
{}
