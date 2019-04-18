#pragma once

#include <queue>

#include <SFML/Graphics.hpp>

#include <ecm.hh>

struct CmpCamera : Component
{
private:
	sf::View                 view_;
	std::queue<sf::Vector2f> buffer_;

public:
	// Class overrides
	CmpCamera() = delete;
	CmpCamera(Entity* const p);
	~CmpCamera();

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};
