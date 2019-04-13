#include "entity_manager.hh"

// Logic
void Entities::update(const float& delta_time)
{
	for (std::size_t i = 0; i < entities_.size(); ++i)
		if (entities_[i]->is_for_deletion())
			entities_.erase(entities_.begin() + i--);
		else
			entities_[i]->update(delta_time);
}

void Entities::render() const
{
	for (const std::unique_ptr<Entity>& e : entities_)
		if (e->is_visible())
			e->render();
}

// Entities
void Entities::clear()
{
	entities_.clear();
}

void Entities::add(std::unique_ptr<Entity> entity)
{
	entities_.push_back(std::move(entity));
}

const std::vector<std::unique_ptr<Entity>>& Entities::list() const
{
	return entities_;
}

const std::vector<Entity*> Entities::find(const std::string& tag) const
{
	std::vector<Entity*> output;
	for (const std::unique_ptr<Entity>& e : entities_)
		if (e->tags().find(tag) != e->tags().end())
			output.push_back(e.get());
	return output;
}

const std::vector<Entity*> Entities::find(const std::vector<std::string>& tags) const
{
	std::vector<Entity*> output;
	for (const std::unique_ptr<Entity>& e : entities_)
		for (const std::string& t : tags)
			if (e->tags().find(t) != e->tags().end())
			{
				output.push_back(e.get());
				break;
			}
	return output;
}

