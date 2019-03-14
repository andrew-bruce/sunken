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
	Renderer::queue(sprite_.get());
}

const sf::Sprite& CmpSprite::sprite() const
{
	return *sprite_;
}
