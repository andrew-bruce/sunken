#pragma once

#include <SFML/Graphics.hpp>

#include <ecm.hh>

struct CmpPickup : Component
{
private:
	sf::Color colour_;
	float distance_;

public:
	// Class overrides
	CmpPickup() = delete;
	explicit CmpPickup(Entity* const p);

	void pickup();
	float distance();

	// Logic (Pure virtual)
	void update(const float& delta_time) override;
	void render() override = 0;
};
