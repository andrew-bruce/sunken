#include "cmp_health.hh"

#include <iostream>
#include <engine.hh>
#include "../sunken.hh"



CmpHealth::CmpHealth(Entity * p) : Component(p){}

float CmpHealth::health()
{
	return health_;
}

void CmpHealth::set_health(float health)
{
	health_ = health;
}

void CmpHealth::update(const float & delta_time)
{
	if (health_ <= 0) {
		// Deletes enemy and makes player invisible if they die for now
		auto player = parent_->scene->entities().find("player").front();
		if (parent_ == player)
			return engine::change_scene(&scene_menu);
		else
			parent_->delete_please();
	}
}
