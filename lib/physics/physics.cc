#include "physics.hh"

namespace physics
{
	// 1 sf unit == 30 physics units
	static constexpr float scale = 30.0f;

	// Inverse is useful
	static constexpr float scale_inv = 1.0f / scale;

	// Physics accuracy
	static constexpr int velocity_iterations = 6;
	static constexpr int position_iterations = 2;

	// Physics world
	static b2World* physics_world;

	// Initialise physics with world
	void initialise(b2World* world)
	{
		physics_world = world;
	}

	// Update world
	void update(const float& delta_time)
	{
		physics_world->Step(
			delta_time,
			velocity_iterations,
			position_iterations);
	}

	// Convert from b2Vec2 to Vector2f
	const sf::Vector2f bv2_to_sv2(const b2Vec2& vector)
	{
		return sf::Vector2f(vector.x, vector.y) * scale;
	}

	// Convert from Vector2f to b2Vec2
	const b2Vec2 sv2_to_bv2(const sf::Vector2f& vector)
	{
		return b2Vec2(vector.x * scale_inv, vector.y * scale_inv);
	}

	// Convert from screenspace to physics
	const sf::Vector2f invert_height(
		const sf::Vector2f& vector,
		const float height)
	{
		return sf::Vector2f(vector.x, height - vector.y);
	}

	// Create a Box2D body with a box fixture
	b2Body* create_box(
		const bool dynamic,
		const sf::Vector2f& position,
		const sf::Vector2f& size)
	{
		// Create shape
		b2PolygonShape shape;
		b2Vec2 size_b2(sv2_to_bv2(size * 0.5f));
		shape.SetAsBox(size_b2.x, size_b2.y);

		// Create fixture
		b2FixtureDef fixture_def;
		fixture_def.density     = dynamic ? 10.0f : 0.0f;
		fixture_def.friction    = dynamic ? 0.8f : 1.0f;
		fixture_def.restitution = 1.0f;
		fixture_def.shape       = &shape;

		// Body properties
		b2BodyDef body_def;
		body_def.type     = dynamic ? b2_dynamicBody : b2_staticBody;
		body_def.position = sv2_to_bv2(position);

		// Create body
		auto body = physics_world->CreateBody(&body_def);
		body->CreateFixture(&fixture_def);
		return body;
	}

	// Create a Box2D body from a sf::RectangleShape
	b2Body* create_box(
		const bool dynamic,
		const sf::RectangleShape& rs)
	{
		return create_box(
			dynamic,
			rs.getPosition(),
			rs.getSize());
	}
}