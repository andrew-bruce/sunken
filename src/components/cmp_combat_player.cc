#include "cmp_combat_player.hh"

CmpCombatPlayer::CmpCombatPlayer(Entity * p) : CmpCombat(p){
	ammo_ = 5;
	fire_cooldown_ = 0;
}

void CmpCombatPlayer::update(const float & delta_time)
 {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		fire();
	}

	CmpCombat::update(delta_time);
}

void CmpCombatPlayer::render()
{
}