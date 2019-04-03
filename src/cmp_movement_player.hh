#pragma once

#include <cmp_movement.hh>

struct CmpMovementPlayer : CmpMovement
{
	// Class overrides
	CmpMovementPlayer() = delete;
	explicit CmpMovementPlayer(Entity* p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};

