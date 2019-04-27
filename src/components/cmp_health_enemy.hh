#pragma once
#include "cmp_health.hh"

struct CmpHealthEnemy : CmpHealth
{
	// Class overrides
	CmpHealthEnemy() = delete;
	explicit CmpHealthEnemy(Entity* p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};
