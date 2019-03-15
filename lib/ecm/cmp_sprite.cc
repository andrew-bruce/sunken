#include "cmp_sprite.hh"

#include <system_renderer.hh>

CmpSprite::CmpSprite(Entity* p)
: Component(p) {};

void CmpSprite::update(const float& delta_time)
{
	sprite_->setPosition(parent_->position());
}

void CmpSprite::render()
{
	renderer::queue(sprite_.get());
}

sf::Sprite& CmpSprite::sprite() const
{
	return *sprite_;
}
