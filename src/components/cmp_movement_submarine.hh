#pragma once

#include "cmp_movement.hh"

struct CmpMovementSubmarine : CmpMovement
{
	// Class overrides
	CmpMovementSubmarine() = delete;
	explicit CmpMovementSubmarine(Entity* const p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;

	// Valid move
	bool valid_move(const sf::Vector2f& movement) override;
};
