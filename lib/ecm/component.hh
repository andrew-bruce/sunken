#pragma once

// Forward declare
struct Entity;

// Component
struct Component
{
protected:
	bool          for_deletion_;
	Entity* const parent_;

public:
	Component() = delete;
	explicit Component(Entity* const p);
	virtual ~Component();

	// Logic
	virtual void update(const float& delta_time) = 0;
	virtual void render() = 0;

	// Deletion
	bool is_for_deletion() const;
};