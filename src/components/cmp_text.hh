#pragma once

#include <SFML/Graphics.hpp>

#include <ecm.hh>

struct CmpText : Component
{
protected:
	sf::Text    text_;
	std::string string_;

public:
	// Class overrides
	CmpText() = delete;
	explicit CmpText(Entity* const p, const std::string& string = "");
	~CmpText() override = default;

	// Logic
	void update(const float& delta_time) override;
	void render() override;

	// Text
	void text(const std::string& string);
	sf::FloatRect bounds() const;
};
