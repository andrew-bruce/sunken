#pragma once

#include "cmp_pickup.hh"

struct CmpPickupAmmo : CmpPickup
{
private:
	sf::Color colour_;

public:
	// Class overrides
	CmpPickupAmmo() = delete;
	explicit CmpPickupAmmo(Entity* const p);

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};
