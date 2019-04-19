#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

#include <SFML/System.hpp>

#include "component.hh"

// Forward declare
struct Entities;
struct Scene;

// Entity
struct Entity
{
	friend struct Entities;

protected:
	// Properties
	sf::Vector2f position_;
	float        rotation_;
	sf::Vector2f scale_;

	// Flags
	bool alive_;
	bool visible_;
	bool for_deletion_;

	// String tags
	std::set<std::string> tags_;

	// Component list
	std::vector<std::unique_ptr<Component>> components_;

public:
	// Scene containing entity
	Scene* const scene;

	// Class overrides
	Entity() = delete;
	explicit Entity(Scene* const scene);
	virtual ~Entity();

	// Logic
	virtual void update(const float& delta_time);
	virtual void render();

	// Position
	sf::Vector2f position() const;
	void move_to(const sf::Vector2f& position);
	void move_by(const sf::Vector2f& movement);

	// Rotation
	float rotation() const;
	void rotate_to(const float& rotation);
	void rotate_by(const float& rotation);

	// Scale
	sf::Vector2f scale() const;
	void scale_to(const sf::Vector2f& scale);
	void scale_by(const sf::Vector2f& scale);

	// Visibility
	bool is_visible() const;
	void visible(const bool& visible);

	// Life
	bool is_alive() const;
	void alive(const bool& alive);

	// Deletion
	bool is_for_deletion() const;
	void delete_please();

	// Tags
	void add_tag(const std::string& t);
	const std::set<std::string>& tags() const;

	// Components
	template <typename T, typename... Targs>
	T* const add_component(Targs... params)
	{
		static_assert(std::is_base_of<Component, T>::value, "T != Component");

		std::unique_ptr<T> component(std::make_unique<T>(this, params...));
		components_.push_back(std::move(component));

		return (T*)components_.back().get();
	}

	template <typename T>
	const std::vector<T*> components() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T != component");

		std::vector<T*> output;
		for (const std::unique_ptr<Component>& c : components_)
			if (typeid(c.get()) == typeid(T))
				output.push_back((T*)c.get());

		return std::move(output);
	}

	template <typename T>
	const std::vector<T*> compatible_components() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T != component");

		std::vector<T*> output;
		for (const std::unique_ptr<Component>& c : components_)
			if (dynamic_cast<T*>(&(*c)))
				output.push_back((T*)c.get());

		return std::move(output);
	}
};
