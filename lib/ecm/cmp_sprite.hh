#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "ecm.hh"

struct CmpSprite : Component
{
protected:
	std::unique_ptr<sf::Sprite> sprite_;

public:
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
};
