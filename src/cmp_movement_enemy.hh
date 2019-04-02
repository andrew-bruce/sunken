#pragma once

// Project
#include <cmp_movement.hh>



struct CmpMovementEnemy : CmpMovement
{
	// Class overrides
	CmpMovementEnemy() = delete;
	explicit CmpMovementEnemy(Entity* p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;

protected:
	enum State
	{
		Roaming,
		Rotating,
		Rotated
	};

	sf::Vector2f direction_;
	State        state_;
};
