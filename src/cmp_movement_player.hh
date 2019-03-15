#pragma once

#include <cmp_movement.hh>

struct CmpMovementPlayer : CmpMovement {
	CmpMovementPlayer() = delete;
	explicit CmpMovementPlayer(Entity* p);

	void update(const float& delta_time) override;
	void render() override;
};