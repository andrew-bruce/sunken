#include "cmp_combat.hh"

#include <iostream>

#include <level_loader.hh>
#include <scene.hh>
#include <maths.hh>
#include <engine.hh>

#include "cmp_movement_torpedo.hh"
#include "cmp_shape.hh"
#include "cmp_sprite.hh"
#include "cmp_sound.hh";

sf::Texture torpedo_texture;

// Class overrides
CmpCombat::CmpCombat(Entity* const p)
: Component(p),
  ammo_(5),
  fire_cooldown_(0.0f)
{}


// Ammo
unsigned CmpCombat::ammo()
{
	return ammo_;
}

void CmpCombat::pickup_ammo(const unsigned& ammo)
{
	ammo_ += ammo;
}

// Logic
void CmpCombat::update(const float& delta_time) {
	if(fire_cooldown_ > 0.0f)
		fire_cooldown_ -= delta_time;
}



// Fires torpedo along direction vector
void CmpCombat::fire(const sf::Vector2f& direction, std::string tag)
{
	if (ammo_ == 0 || fire_cooldown_ > 0.0f)
		return;

	auto size = sf::Vector2f(level::tile_size(), level::tile_size()) / 48.f;

	auto e = parent_->scene->make_entity();
	e->move_to(parent_->position());

	auto t = e->add_component<CmpMovementTorpedo>(direction);
	e->add_tag(tag);

	if (tag == "enemy_torpedo" || tag == "player_torpedo")
	{
		t->set_speed(40.f);
		fire_cooldown_ = 3.f;
	}
	else
	{
		size = sf::Vector2f(level::tile_size(), level::tile_size()) / 16.f;
		t->set_speed(15.f);
		fire_cooldown_ = 5.f;
	}

	auto s = e->add_component<CmpShape>();
	s->use_shape<sf::CircleShape>(size.x);
	s->shape().setOrigin(size);
	s->shape().setFillColor(sf::Color(232, 232, 232));

	--ammo_;
}
