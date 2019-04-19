#pragma once

#include "cmp_movement.hh"

struct CmpMovementEnemy : CmpMovement
{
protected:
	enum State
	{
		Roaming,
		Rotating,
		Rotated
	};

	sf::Vector2f direction_;
	State        state_;

public:
	// Class overrides
	CmpMovementEnemy() = delete;
	explicit CmpMovementEnemy(Entity* const p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};
