#pragma once

#include "ecm.hh"

struct CmpCombat : Component
{
protected:
	unsigned ammo_;
	float    fire_cooldown_;

public:
	// Class overrides
	CmpCombat() = delete;
	explicit CmpCombat(Entity* const p);

	// Ammo
	unsigned ammo();
	void     pickup_ammo(const unsigned& ammo);

	// Logic (Pure virtual)
	void update(const float& delta_time) override;
	void render() override = 0;

	// Fires torpedo along direction vector
	void     fire(const sf::Vector2f& direction);
};
