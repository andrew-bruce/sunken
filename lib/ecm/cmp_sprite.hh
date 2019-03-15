#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "ecm.hh"

struct CmpSprite : Component {
	CmpSprite() = delete;
	explicit CmpSprite(Entity* p);
	~CmpSprite() = default;

	void update(const float& delta_time) override;
	void render() override;

	sf::Sprite& sprite() const;

	template <typename T, typename... Targs>
	void use_sprite(Targs... params) {
		sprite_.reset(new T(params...));
	}

protected:
	std::unique_ptr<sf::Sprite> sprite_;
};