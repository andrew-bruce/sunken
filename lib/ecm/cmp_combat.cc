#include "cmp_combat.hh"

#include <system_renderer.hh>
#include <level_system.hh>
#include <iostream>


CmpCombat::CmpCombat(Entity* p) : Component(p) {
	ammo_ = 5;
}

// fires missile
void CmpCombat::fire() 
{
	if (ammo_ <= 0)
		return;
	if (fire_cooldown_ > 0)
		return;
	
	std::cout << "FIRE" << std::endl;
	ammo_ --;
	fire_cooldown_+= 5;
	// create missile object
	// sets it's position
	// set its speed a trajectory
}

// checks ammo
float CmpCombat::get_ammo_count() 
{
	return ammo_;
}

// adds more ammo upon pickup
void CmpCombat::set_ammo(float pickup) 
{
	ammo_ += pickup;
}

void CmpCombat::update(const float& delta_time) {
	if(fire_cooldown_ > 0)
		fire_cooldown_ -= delta_time;
}