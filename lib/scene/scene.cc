#include "scene.hh"

// Loading
void Scene::loaded(bool b) const
{
	std::lock_guard<std::mutex> lock(loaded_mutex_);
	loaded_ = b;
}

bool Scene::is_loaded() const
{
	std::lock_guard<std::mutex> lock(loaded_mutex_);

	if (loaded_future_.valid() &&
	    loaded_future_.wait_for(std::chrono::seconds(0))
		== std::future_status::ready)
	{
		loaded_future_.get();
		loaded_ = true;
	}

	return loaded_;
}

void Scene::load_async()
{
	loaded_future_ = std::async(&Scene::load, this);
}

void Scene::unload()
{
	entities_.clear();
	loaded(false);
}

// Logic
void Scene::update(const float& delta_time)
{
	entities_.update(delta_time);
}

void Scene::render()
{
	entities_.render();
}

// Entities
Entity* Scene::make_entity()
{
	auto e = std::make_unique<Entity>(this);
	return entities_.add(std::move(e));
}

const Entities& Scene::entities() const
{
	return entities_;
}
