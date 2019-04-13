#include "cmp_shape.hh"

#include <system_renderer.hh>

// Class overrides
CmpShape::CmpShape(Entity* p) : Component(p) {};

// Logic
void CmpShape::update(const float& delta_time)
{
	shape_->setPosition(parent_->position());
}

void CmpShape::render()
{
	renderer::queue(shape_.get());
}

// Reference to shape
sf::Shape& CmpShape::shape() const
{
	return *shape_;
}

