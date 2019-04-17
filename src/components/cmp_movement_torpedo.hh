#pragma once

#include <ecm.hh>
#include "cmp_movement.hh"
#include <maths.hh>
#include <engine.hh>

struct CmpMovementTorpedo : CmpMovement
{
private:
	sf::Vector2f direction_;

public:
	// Class overrides
	CmpMovementTorpedo() = delete;
	explicit CmpMovementTorpedo(Entity* p, sf::Vector2f direction);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};

