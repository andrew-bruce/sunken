#pragma once

#include "entity_manager.hh"

struct Scene {
	Scene() = default;
	virtual ~Scene() = default;
	Scene(Scene&&) = default;
	Scene(const Scene&) = default;
	Scene& operator=(Scene&&) = default;
	Scene& operator=(const Scene&) = default;

	virtual void update(const float& delta_time);
	virtual void render();
	virtual void load() = 0;

protected:
	Entities entities_;
};
