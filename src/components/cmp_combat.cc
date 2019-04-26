#include "cmp_combat.hh"

#include <iostream>

#include <level_loader.hh>
#include <scene.hh>

#include "cmp_movement_torpedo.hh"
#include "cmp_shape.hh"
#include "cmp_sprite.hh"

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

	auto e = parent_->scene->make_entity();
	e->move_to(parent_->position());

	// Set torpedo texture an scales
	if (direction.x > 0)
		torpedo_texture.loadFromFile("res/img/torpedo-right.png");
	else
		torpedo_texture.loadFromFile("res/img/torpedo-left.png");


	auto s = e->add_component<CmpSprite>();
	s->use_sprite<sf::Sprite>();
	s->sprite().setTexture(torpedo_texture);
	s->sprite().setScale(0.05, 0.05);

	// Gets size of texture divided by 10 to account for scaling
	const auto size = sf::Vector2f(s->sprite().getTexture()->getSize().x / 10, s->sprite().getTexture()->getSize().y / 20);

	auto t = e->add_component<CmpMovementTorpedo>(direction);
	e->add_tag(tag);
	
	if (tag == "enemy_torpedo" || tag == "player_torpedo") 
	{
		t->set_speed(40.f);
	}
	else 
	{
		t->set_speed(15.f);
	}

	--ammo_;
	fire_cooldown_ = 3.f;
}
