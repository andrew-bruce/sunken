#include "cmp_camera.hh"

#include <iostream>

#include <level_loader.hh>
#include <engine.hh>

// Class overrides
CmpCamera::CmpCamera(Entity* const p)
: Component(p)
{}

CmpCamera::~CmpCamera()
{
	engine::window().setView(engine::window().getDefaultView());
}

// Logic
void CmpCamera::update(const float& delta_time)
{
	buffer_.push(parent_->position());
	if (buffer_.size() > 1000)
		buffer_.pop();
}

void CmpCamera::render()
{
	float scale       = level::tile_size() * 4.0f;
	sf::Vector2f size = sf::Vector2f(scale, scale);

	// Make view fill screen
	auto& window = engine::window();
	auto  w_size = sf::cast<float>(window.getSize());
	if (w_size.x < w_size.y)
		size.x *= w_size.x / w_size.y;
	else
		size.y *= w_size.y / w_size.x;

	view_.setCenter(buffer_.front());
	view_.setSize(size);
	window.setView(view_);
}
