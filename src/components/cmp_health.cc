#include "cmp_health.hh"

#include <engine.hh>

#include "cmp_sound_temp.hh"
#include "../sunken.hh"



CmpHealth::CmpHealth(Entity * p, float health) : Component(p)
{
	health_ = health;
}

float CmpHealth::health() const
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
		{
			parent_->delete_please();

			// Plays explosion on distruction of enemy
			auto e = parent_->scene->make_entity();
			auto sound = e->add_component<CmpSoundTemp>("distruction.ogg");
			sound->sound().setVolume(20);
			auto s = e->compatible_components<CmpSoundTemp>().front();
			s->sound().play();
		}
	}
}

void CmpHealth::render(){}
