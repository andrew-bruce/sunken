#include "cmp_health_enemy.hh"

CmpHealthEnemy::CmpHealthEnemy(Entity * p) : CmpHealth(p) { health_ = 80.f; }

void CmpHealthEnemy::update(const float & delta_time)
{
	CmpHealth::update(delta_time);
}

void CmpHealthEnemy::render(){}
