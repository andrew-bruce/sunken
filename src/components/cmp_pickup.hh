#pragma once
#include "ecm.hh"
#include "cmp_shape.hh"
#include "scene.hh"

struct CmpPickup : Component
{
private:
	sf::Color colour_;
	float distance_;

public:
	// Class overrides
	CmpPickup() = delete;
	explicit CmpPickup(Entity* p);

	void pickup();
	float distance();

	// Logic (Pure virtual)
	void update(const float& delta_time) override;
	void render() override = 0;
};
