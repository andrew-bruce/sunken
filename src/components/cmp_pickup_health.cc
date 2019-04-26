#include "cmp_pickup_health.hh"
#include "cmp_health_player.hh"
#include "cmp_sound.hh"
#include "cmp_shape.hh"

#include <iostream>

#include <level_loader.hh>
#include <scene.hh>

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

	if (picked_up()) {
		// Gets player
		auto player = parent_->scene->entities().find("player").front();

		// Set pickup sound
		auto e = parent_->scene->make_entity();
		auto sound = e->add_component<CmpSound>("health-pickup.ogg");
		sound->sound().setVolume(20);
		auto s = e->compatible_components<CmpSound>().front();
		s->sound().play();

		// Gets it's health component
		auto h = player->compatible_components<CmpHealthPlayer>().front();

		// Increase health
		if (h->health() <= 70)
		{
			h->set_health(h->health() + 30);
			std::cout << "Health: " << h->health() << std::endl;
		}
		else
		{
			h->set_health(h->health() + 100 - h->health());
			std::cout << "Health: " << h->health() << std::endl;
		}
	}
}

void CmpPickupHealth::render()
{}
