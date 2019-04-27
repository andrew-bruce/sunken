#pragma once

#include <memory>

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>

namespace physics
{
	// Initialise physics with world
	void initialise(b2World* world = nullptr);

	// Cleanup
	void cleanup();

	// Current physics world
	const b2World* world();

	// List of bodies in world
	const std::vector<b2Body*> bodies();

	// Update world
	void update(const float& delta_time);

	// Create a Box2D body with a box fixture
	b2Body* create_box(
		const bool dynamic,
		const sf::Vector2f& position,
		const sf::Vector2f& size);

	// Create a Box2D body from a sf::RectangleShape
	b2Body* create_box(
		const bool dynamic,
		const sf::RectangleShape& rs);




	// Convert from b2Vec2 to Vector2f
	const sf::Vector2f bv2_to_sv2(const b2Vec2& vector);

	// Convert from Vector2f to b2Vec2
	const b2Vec2 sv2_to_bv2(const sf::Vector2f& vector);

	// Convert from screenspace to physics
	const sf::Vector2f invert_height(
		const sf::Vector2f& vector,
		const float height);
}
