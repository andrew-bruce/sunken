#include "entity_manager.hh"



void Entities::update(const float& delta_time) const
{
	for (const auto& entity : entities_)
		entity->update(delta_time);
}



void Entities::render() const
{
	for (const auto& entity : entities_)
		entity->render();
}



// ENTITIES
void Entities::add(std::unique_ptr<Entity> entity)
{
	entities_.push_back(std::move(entity));
}

void Entities::clear()
{
	entities_.clear();
}
