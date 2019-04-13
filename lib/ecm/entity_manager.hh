#pragma once

#include <memory>
#include <vector>

#include "entity.hh"

// Entity manager
struct Entities
{
private:
	std::vector<std::unique_ptr<Entity>> entities_;

public:
	// Logic
	void update(const float& delta_time) const;
	void render() const;

	// Entities
	void add(std::unique_ptr<Entity> entity);
	void clear();
};

