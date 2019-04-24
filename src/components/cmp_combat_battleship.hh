#pragma once
#include "cmp_combat.hh"

struct CmpCombatBattleship : CmpCombat
{
	// Class overrides
	CmpCombatBattleship() = delete;
	explicit CmpCombatBattleship(Entity* const p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};
