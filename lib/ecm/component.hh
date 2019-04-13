#pragma once

// Forward declare
struct Entity;

// Component
struct Component
{
	friend struct Entity;

protected:
	bool          for_deletion_;
	Entity* const parent_;

	explicit Component(Entity* const p);

public:
	Component() = delete;
	virtual ~Component();

	// Logic
	virtual void update(const float& delta_time) = 0;
	virtual void render() = 0;

	// Deletion
	bool is_for_deletion() const;
};