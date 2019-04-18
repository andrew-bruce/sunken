#pragma once
#include "cmp_pickup.hh"

struct CmpPickupHealth : CmpPickup
{
private:
	sf::Color colour_;

public:
	// Class overrides
	CmpPickupHealth() = delete;
	explicit CmpPickupHealth(Entity* p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};
