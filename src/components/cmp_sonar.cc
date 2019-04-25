#include "cmp_sonar.hh"

#include <string>
#include <vector>

#include <maths.hh>
#include <level_loader.hh>
#include <scene.hh>
#include <engine.hh>

#include "cmp_shape.hh"
#include "cmp_sound.hh"

#define MAX_COOLDOWN 4.0f
#define MAX_STRENGTH 255

// Class overrides
CmpSonar::CmpSonar(Entity* const p)
: Component(p),
  cooldown_(0.0f),
  radius_(0.0f),
  speed_(level::tile_size() * 1.25f),
  strength_(0)
{}



// Logic
void CmpSonar::update(const float& delta_time)
{
	if (engine::keyboard[sf::Keyboard::Space]
	 && cooldown_ <= 0.0f)
	{
		const auto player = parent_->scene->entities().find("player").front();
		if (!player)
			return;

		parent_->move_to(player->position());
		strength_ = 255;
		radius_ = 0.0f;
		cooldown_ = MAX_COOLDOWN;

		const auto sound = parent_->compatible_components<CmpSound>().front();
		if (sound)
			if (sound->loaded())
				sound->sound().play();
	}

	// Catch negative cooldown
	if (cooldown_ < 0.0f)
		cooldown_ = 0.0f;

	// Update values
	if (cooldown_ > 0.0f)
	{
		cooldown_ -= delta_time;
		radius_ += speed_ * delta_time;
		strength_ = std::pow(cooldown_ / MAX_COOLDOWN, 2) * MAX_STRENGTH;
	}

	// Update own shape
	{
		auto shape = parent_->compatible_components<CmpShape>().front();
		if (shape)
		{
			auto s = dynamic_cast<sf::CircleShape*>(&shape->shape());
			if (s)
			{
				s->setRadius(radius_);
				s->setOrigin(sf::Vector2f(radius_, radius_));
				s->setOutlineColor(sf::Color(255, 255, 255, strength_));
			}
		}
	}

	// Update other shapes
	{
		static const std::vector<std::string> tags
		{
			"submarine",
			"battleship",
			"objective",
			"pickup",
			"enemy_torpedo",
			"battleship_bomb"
		};

		const auto entities = parent_->scene->entities().find(tags);
		for (const auto e : entities)
		{
			const float distance = sf::length2(e->position() - parent_->position());
			if (distance < std::pow(radius_, 2))
			{
				e->visible(true);

				auto shape = e->compatible_components<CmpShape>().front();
				if (shape)
				{
					auto colour = shape->shape().getFillColor();
					colour.a = strength_;
					shape->shape().setFillColor(colour);
				}
			}
			else
			{
				e->visible(false);
			}
		}
	}
}

void CmpSonar::render()
{

}
