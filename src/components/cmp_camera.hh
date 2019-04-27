#pragma once

#include <queue>

#include <SFML/Graphics.hpp>

#include <ecm.hh>

struct CmpCamera : Component
{
private:
	sf::View     view_;
	sf::Vector2f buffer_;
	float        easing_;

public:
	float        zoom;

	// Class overrides
	CmpCamera() = delete;
	explicit CmpCamera(Entity* const p);
	~CmpCamera();

	// Logic
	void update(const float& delta_time) override;
	void render() override;
};
