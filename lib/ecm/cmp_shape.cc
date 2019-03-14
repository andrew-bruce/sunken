#include "cmp_shape.hh"

#include <system_renderer.hh>

CmpShape::CmpShape(Entity* p)
: Component(p) {};

void CmpShape::update(const float& delta_time)
{
	shape_->setPosition(parent_->position());
}

void CmpShape::render()
{
	Renderer::queue(shape_.get());
}

const sf::Shape& CmpShape::shape() const
{
	return *shape_;
}
