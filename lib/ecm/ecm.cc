#include "ecm.hh"


// Entity
Entity::Entity() { }
Entity::~Entity() { }

// Logic
void Entity::update(const float& delta_time)
{
	for (auto& c : components_)
		c->update(delta_time);
}

void Entity::render()
{
	for (auto& c : components_)
		c->render();
}

// Position
sf::Vector2f Entity::position() const
{
	return position_;
}

void Entity::move_to(const sf::Vector2f& position)
{
	position_ = position;
}

void Entity::move_by(const sf::Vector2f& movement)
{
	position_ += movement;
}

// Rotation
float Entity::rotation() const
{
	return rotation_;
}

void Entity::rotate_to(const float& rotation)
{
	rotation_ = rotation;
}

void Entity::rotate_by(const float& rotation)
{
	rotation_ += rotation;
}

// Scale
sf::Vector2f Entity::scale() const
{
	return scale_;
}

void Entity::scale_to(const sf::Vector2f& scale)
{
	scale_ = scale;
}

void Entity::scale_by(const sf::Vector2f& scale)
{
	scale_ += scale;
}

// Visibility
bool Entity::is_visible() const
{
	return visible_;
}

void Entity::visible(const bool& visible)
{
	visible_ = visible;
}

// Life
bool Entity::is_alive() const
{
	return alive_;
}

void Entity::alive(const bool& alive)
{
	alive_ = alive;
}

// Deletion
bool Entity::is_for_deletion() const
{
	return for_deletion_;
}

void Entity::delete_please()
{
	for_deletion_ = true;
}



// Component
Component::~Component() { }

// Deletion
bool Component::is_for_deletion() const
{
	return for_deletion_;
}

Component::Component(Entity* const p)
: parent_(p) { }
