#pragma once
#include "ecm.hh"

struct CmpHealth : Component
{
protected:
	float health_;

public:
	// Class overrides
	CmpHealth() = delete;
	explicit CmpHealth(Entity* p);

	// combat logic
	float health();
	void set_health(float health);

	// Logic (Pure virtual)
	void update(const float& delta_time) override = 0;
	void render() override = 0;
};
