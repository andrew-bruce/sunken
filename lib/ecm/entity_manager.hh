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
	void update(const float& delta_time);
	void render() const;

	// Entities
	const std::vector<std::unique_ptr<Entity>>& list() const;
	void                                        clear();

	Entity*                    add(std::unique_ptr<Entity> entity);
	const std::vector<Entity*> find(const std::string& tag) const;
	const std::vector<Entity*> find(const std::vector<std::string>& tags) const;
};
