#pragma once

#include <SFML/Graphics.hpp>

#include <ecm.hh>

struct CmpText : Component
{
	sf::Text text;

	// Class overrides
	CmpText() = delete;
	explicit CmpText(Entity* const p, const std::string& string = "");
	~CmpText() override = default;

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};
