#include "cmp_pickup_ammo.hh"

#include <iostream>

#include <SFML/Graphics.hpp>

#include <level_loader.hh>
#include <scene.hh>

#include "cmp_combat.hh"
#include "cmp_shape.hh"
#include "cmp_sound_temp.hh"

// Class overrides
CmpPickupAmmo::CmpPickupAmmo(Entity * const p)
: CmpPickup(p),
  colour_(sf::Color::Cyan)
{
	auto size = sf::Vector2f(level::tile_size(), level::tile_size()) / 16.0f;
	auto s = parent_->add_component<CmpShape>();
	s->use_shape<sf::RectangleShape>(size);
	s->shape().setOrigin(size / 2.0f);
	s->shape().setFillColor(colour_);
}



// Logic
void CmpPickupAmmo::update(const float & delta_time)
{
	CmpPickup::update(delta_time);

	if (picked_up())
	{
		// Gets player
		auto player = parent_->scene->entities().find("player").front();

		// Set pickup sound
		auto e = parent_->scene->make_entity();
		auto sound = e->add_component<CmpSoundTemp>("ammo-pickup.ogg");
		sound->sound().setVolume(20);
		sound->sound().play();

		// Gets it's combat component
		auto c = player->compatible_components<CmpCombat>().front();

		// Increase ammo
		c->pickup_ammo(5);

		std::cout << "Ammo: " << c->ammo() << std::endl;
	}
}

void CmpPickupAmmo::render()
{}
