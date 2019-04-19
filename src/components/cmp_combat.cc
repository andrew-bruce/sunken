#include "cmp_combat.hh"
#include "cmp_movement_torpedo.hh"

#include <iostream>

#include <level_loader.hh>
#include <scene.hh>

CmpCombat::CmpCombat(Entity* p)
: Component(p),
  ammo_(5),
  fire_cooldown_(0.0f)
{}

// fires missile
void CmpCombat::fire(sf::Vector2f direction)
{
	if (ammo_ == 0)
		return;
	if (fire_cooldown_ > 0.0f)
		return;

	std::cout << "FIRE" << std::endl;

	auto size = sf::Vector2f(level::tile_size(), level::tile_size()) / 32.0f;

	auto e = parent_->scene->make_entity();
	e->move_to(parent_->position());

	auto s = e->add_component<CmpShape>();
	s->use_shape<sf::CircleShape>(size.x);
	s->shape().setOrigin(size);
	s->shape().setFillColor(sf::Color::Red);

	auto t = e->add_component<CmpMovementTorpedo>(direction);

	--ammo_;
	fire_cooldown_ = 2.0f;
}

// checks ammo
unsigned CmpCombat::ammo()
{
	return ammo_;
}

// adds more ammo upon pickup
void CmpCombat::set_ammo(unsigned pickup)
{
	ammo_ += pickup;
}

void CmpCombat::update(const float& delta_time) {
	if(fire_cooldown_ > 0.0f)
		fire_cooldown_ -= delta_time;
}
