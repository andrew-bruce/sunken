#pragma once
#include "ecm.hh"
#include "cmp_shape.hh"
#include <iostream>

struct CmpCombat : Component
{
protected:
	float ammo_;
	float fire_cooldown_;

public:
	// Class overrides
	CmpCombat() = delete;
	explicit CmpCombat(Entity* p);

	// combat logic
	void fire();
	float get_ammo_count();
	void set_ammo(float pickup);

	// Logic (Pure virtual)
	void update(const float& delta_time) override;
	void render() override = 0;
};

