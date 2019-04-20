#include "cmp_health_player.hh"


CmpHealthPlayer::CmpHealthPlayer(Entity * p) : CmpHealth(p) { health_ = 100.f; }

void CmpHealthPlayer::update(const float & delta_time)
{
	CmpHealth::update(delta_time);
}

void CmpHealthPlayer::render(){}
