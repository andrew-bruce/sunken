#include "entity.hh"

// Class oveerrides
Entity::Entity(Scene* const scene)
 : position_    (sf::Vector2f(0.0f, 0.0f)),
   rotation_    (0.0f),
   scale_       (sf::Vector2f(0.0f, 0.0f)),
   alive_       (true),
   visible_     (true),
   for_deletion_(false),
   scene        (scene)
{}
Entity::~Entity() {}

// Logic
void Entity::update(const float& delta_time)
{
	if (!alive_)
		return;

	for (std::size_t i(0); i < components_.size(); ++i)
		if (components_[i]->is_for_deletion())
			components_.erase(components_.begin() + i--);
		else
			components_[i]->update(delta_time);
}

void Entity::render()
{
	if (!visible_)
		return;

	for (const std::unique_ptr<Component>& c : components_)
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
	alive_ = false;
	visible_ = false;
	for_deletion_ = true;
}

// Tags
void Entity::add_tag(const std::string& t)
{
	tags_.insert(t);
}

const std::set<std::string>& Entity::tags() const
{
	return tags_;
}
