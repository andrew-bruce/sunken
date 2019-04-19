#pragma once

#include "cmp_movement.hh"

struct CmpMovementTorpedo : CmpMovement
{
private:
	sf::Vector2f direction_;

public:
	// Class overrides
	CmpMovementTorpedo() = delete;
	explicit CmpMovementTorpedo(Entity* const p, const sf::Vector2f& direction);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};

