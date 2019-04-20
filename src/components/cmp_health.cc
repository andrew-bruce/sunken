#include "cmp_health.hh"
#include<scene.hh>


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
			parent_->visible(false);
		else
			parent_->delete_please();
	}
}
