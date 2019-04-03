#pragma once

#include "entity_manager.hh"

struct Scene
{
protected:
	Entities entities_;

public:
	// Class overrides
	virtual ~Scene() = default;

	// Logic
	virtual void update(const float& delta_time);
	virtual void render();
	virtual void load() = 0;
};
