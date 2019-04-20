#pragma once
#include "ecm.hh"
#include "cmp_shape.hh"
#include "scene.hh"

struct CmpPickup : Component
{
private:
	sf::Color colour_;
	float distance_;
	bool picked_up_ = false;

public:
	// Class overrides
	CmpPickup() = delete;
	explicit CmpPickup(Entity* p);

	void pickup();
	bool picked_up();

	// Logic (Pure virtual)
	void update(const float& delta_time) override;
	void render() override = 0;
};
