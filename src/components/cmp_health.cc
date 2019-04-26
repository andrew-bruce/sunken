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
	if (health_ <= 0)
	{
		if (parent_->tags().find("player") != parent_->tags().end())
			parent_->visible(false);
		else
			parent_->delete_please();
	}
}
