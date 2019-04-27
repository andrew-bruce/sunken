#pragma once
#include "cmp_health.hh"

struct CmpHealthPlayer : CmpHealth
{
	// Class overrides
	CmpHealthPlayer() = delete;
	explicit CmpHealthPlayer(Entity* p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};
