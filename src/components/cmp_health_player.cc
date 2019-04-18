#include "cmp_health_player.hh"


CmpHealthPlayer::CmpHealthPlayer(Entity * p) : CmpHealth(p){}

void CmpHealthPlayer::update(const float & delta_time)
{
	// Check if hit by torpedo or crash into wall, reduce health if so
}

void CmpHealthPlayer::render(){}
