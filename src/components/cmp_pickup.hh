#pragma once

#include <SFML/Graphics.hpp>

#include <ecm.hh>

struct CmpPickup : Component
{
private:
	sf::Color colour_;
	float distance_;
	bool picked_up_ = false;

public:
	// Class overrides
	CmpPickup() = delete;
	explicit CmpPickup(Entity* const p);

	void pickup();
	bool picked_up();

	// Logic (Pure virtual)
	void update(const float& delta_time) override;
	void render() override = 0;
};
