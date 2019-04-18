#pragma once
#include "ecm.hh"
#include "cmp_shape.hh"
#include "scene.hh"

struct CmpPickup : Component
{
private:
	sf::Color colour_;

public:
	// Class overrides
	CmpPickup() = delete;
	explicit CmpPickup(Entity* p);

	void pickup();

	// Logic (Pure virtual)
	void update(const float& delta_time) override = 0;
	void render() override = 0;
};
