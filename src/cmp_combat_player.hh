#pragma once

#include <cmp_combat.hh>
#include "cmp_torpedo.hh"

struct CmpCombatPlayer : CmpCombat
{
	// Class overrides
	CmpCombatPlayer() = delete;
	explicit CmpCombatPlayer(Entity* p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};

