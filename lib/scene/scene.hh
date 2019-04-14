#pragma once

#include <future>
#include <mutex>

#include <entity_manager.hh>

struct Scene
{
private:
	// Mutex
	mutable bool loaded_;
	mutable std::future<void> loaded_future_;
	mutable std::mutex loaded_mutex_;

protected:
	// Entities
	Entities entities_;

	void loaded(bool l);

public:
	// Class overrides
	virtual ~Scene() = default;

	// Loading
	bool is_loaded() const;
	virtual void load() = 0;
	virtual void load_async();
	virtual void unload();

	// Logic
	virtual void update(const float& delta_time);
	virtual void render();

	// Entities
	Entity* make_entity();
};
