#pragma once

#include "cmp_combat.hh"

struct CmpCombatPlayer : CmpCombat
{
	// Class overrides
	CmpCombatPlayer() = delete;
	explicit CmpCombatPlayer(Entity* const p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};
