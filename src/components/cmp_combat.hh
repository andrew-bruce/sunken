#pragma once
#include "ecm.hh"
#include "cmp_shape.hh"
#include "scene.hh"

struct CmpCombat : Component
{
protected:
	unsigned ammo_;
	float fire_cooldown_;

public:
	// Class overrides
	CmpCombat() = delete;
	explicit CmpCombat(Entity* p);

	// combat logic
	void fire(sf::Vector2f direction);
	unsigned ammo();
	void pickup_ammo(unsigned ammo);

	// Logic (Pure virtual)
	void update(const float& delta_time) override;
	void render() override = 0;
};
