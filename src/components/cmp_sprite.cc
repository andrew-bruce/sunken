#include "cmp_sprite.hh"

#include <renderer.hh>

// Class overrides
CmpSprite::CmpSprite(Entity* const p)
: Component(p)
{}

// Logic
void CmpSprite::update(const float& delta_time)
{
	sprite_->setPosition(parent_->position());
}

void CmpSprite::render()
{
	renderer::queue(sprite_.get());
}

// Reference to sprite
sf::Sprite& CmpSprite::sprite() const
{
	return *sprite_;
}

sf::Texture CmpSprite::texture()
{
	return texture_;
}

void CmpSprite::set_texture(sf::Texture texture)
{
	texture_ = texture;
}

