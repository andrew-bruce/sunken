#pragma once

// Forward declare
struct Entity;

// Component
struct Component
{
	friend struct Entity;

protected:
	Entity* const parent_;
	bool          for_deletion_;

	explicit Component(Entity* const p);

public:
	Component() = delete;
	virtual ~Component();

	virtual void update(const float& delta_time) = 0;
	virtual void render() = 0;

	bool is_for_deletion() const;
};