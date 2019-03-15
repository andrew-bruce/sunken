#pragma once

#include "ecm.hh"

struct CmpMovement : Component {
	CmpMovement() = delete;

	// Move
	void move(const sf::Vector2f& move);
	void move(const float& x, const float& y);

	// Logic
	void update(const float& delta_time) override = 0;
	void render() override = 0;

	// Speed
	float speed_;

protected:
	explicit CmpMovement(Entity* p);
	
	// Whether position is a valid move
	bool valid_move(sf::Vector2f& position);
};