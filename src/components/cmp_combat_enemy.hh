#pragma once

#include "cmp_combat.hh"

struct CmpCombatEnemy : CmpCombat
{
	// Class overrides
	CmpCombatEnemy() = delete;
	explicit CmpCombatEnemy(Entity* const p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};
