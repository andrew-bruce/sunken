#pragma once

#include "ecm.hh"

struct CmpMovement : Component
{
protected:
	float speed_;
	explicit CmpMovement(Entity* p);

public:
	// Class overrides
	CmpMovement() = delete;

	// Move
	void move(const sf::Vector2f& move);
	void move(const float& x, const float& y);

	// Logic (Pure virtual)
	void update(const float& delta_time) override = 0;
	void render() override = 0;

	// Whether position is a valid move
	bool valid_move(sf::Vector2f& position);
};

