#pragma once

#include "cmp_movement.hh"

struct CmpMovementSubmarine : CmpMovement
{
protected:
	enum State
	{
		Patrol,
		Centering,
		Scanning,
		Rotating,
		Rotated
	};

	State        state_;

	sf::Vector2f direction_;
	sf::Vector2f target_;
	float        scan_time_;

public:

	// Class overrides
	CmpMovementSubmarine() = delete;
	explicit CmpMovementSubmarine(Entity* const p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;

	// Valid move
	bool valid_move(const sf::Vector2f& movement) override;
};
