#include "cmp_movement_player.hh"
#include "cmp_sprite.hh"

#include "../src/sunken.hh"
#include <maths.hh>
#include <level_loader.hh>
#include <engine.hh>
#include <iostream>
#include "resources.hh"


// Class overrides
CmpMovementPlayer::CmpMovementPlayer(Entity* const p)
: CmpMovement(p) {}

// Logic
void CmpMovementPlayer::update(const float& delta_time)
{
	// Gets parent sprite
	auto s = parent_->compatible_components<CmpSprite>().front();

	// Input decides direction vector
	sf::Vector2f movement(0.0f, 0.0f);

	if (engine::keyboard[sf::Keyboard::W])
		--movement.y;
	if (engine::keyboard[sf::Keyboard::A])
	{
		s->sprite().setScale(-std::abs(s->sprite().getScale().x), s->sprite().getScale().y);
		--movement.x;
	}
	if (engine::keyboard[sf::Keyboard::S])
		++movement.y;
	if (engine::keyboard[sf::Keyboard::D])
	{
		s->sprite().setScale(std::abs(s->sprite().getScale().x), s->sprite().getScale().y);
		++movement.x;
	}

	// Normalise movement vector
	movement  = sf::normalise(movement);
	movement *= speed_ * delta_time;

	// Move player
	move(movement);
}

void CmpMovementPlayer::render()
{}



// Valid move
bool CmpMovementPlayer::valid_move(const sf::Vector2f& movement)
{
	const auto tile  = level::tile_at(parent_->position() + movement);
	const auto tiles = level::tiles_of_type(level::TileType::Water);

	// Player can only move in water
	return tiles.find(tile) != tiles.end();
}
