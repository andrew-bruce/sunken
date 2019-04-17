#include "cmp_combat_player.hh"

#include <engine.hh>

CmpCombatPlayer::CmpCombatPlayer(Entity * p) : CmpCombat(p) {}

void CmpCombatPlayer::update(const float & delta_time)
 {
	if (engine::keyboard[sf::Keyboard::Space])
		fire();

	CmpCombat::update(delta_time);
}

void CmpCombatPlayer::render() {}
