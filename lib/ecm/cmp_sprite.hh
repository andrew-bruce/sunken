#pragma once

#include <memory>

// SFML
#include <SFML/Graphics.hpp>

// Project
#include "ecm.hh"



struct CmpSprite : Component
{
	// Class overrides
	CmpSprite() = delete;
	explicit CmpSprite(Entity* p);
	~CmpSprite() = default;

	// Logic
	void update(const float& delta_time) override;
	void render() override;

	// Reference to sprite
	sf::Sprite& sprite() const;

	// Replaces sprite used
	template <typename T, typename... Targs>
	void use_sprite(Targs... params) {
		sprite_.reset(new T(params...));
	}

protected:
	std::unique_ptr<sf::Sprite> sprite_;
};