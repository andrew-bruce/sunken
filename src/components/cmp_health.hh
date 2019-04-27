#pragma once
#include "ecm.hh"

struct CmpHealth : Component
{
protected:
	float health_;

public:
	// Class overrides
	CmpHealth() = delete;
	explicit CmpHealth(Entity* p, float health);

	// combat logic
	float health() const;
	void set_health(float health);

	// Logic (Pure virtual)
	void update(const float& delta_time) override;
	void render() override;
};
