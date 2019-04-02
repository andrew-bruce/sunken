#pragma once

#include "entity_manager.hh"

struct Scene
{
	// Class overrides
	virtual ~Scene() = default;

	// Logic
	virtual void update(const float& delta_time);
	virtual void render();
	virtual void load() = 0;

protected:
	Entities entities_;
};
