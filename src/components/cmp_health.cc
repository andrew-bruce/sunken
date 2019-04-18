#include "cmp_health.hh"


CmpHealth::CmpHealth(Entity * p) : Component(p){}

float CmpHealth::health()
{
	return health_;
}

void CmpHealth::set_health(float health)
{
	health_ = health;
}
