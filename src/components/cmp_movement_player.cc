#include "cmp_movement_player.hh"

#include <maths.hh>
#include <level_loader.hh>
#include <engine.hh>

// Class overrides
CmpMovementPlayer::CmpMovementPlayer(Entity* const p)
: CmpMovement(p) {}

// Logic
void CmpMovementPlayer::update(const float& delta_time)
{
	// Input decides direction vector
	sf::Vector2f movement(0.0f, 0.0f);

	// Prevents player from going above surface of water
	if (engine::keyboard[sf::Keyboard::W])
		--movement.y;
	if (engine::keyboard[sf::Keyboard::A])
		--movement.x;
	if (engine::keyboard[sf::Keyboard::S])
		++movement.y;
	if (engine::keyboard[sf::Keyboard::D])
		++movement.x;

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
	auto tile  = level::tile_at(parent_->position() + movement);
	auto tiles = level::tiles_of_type(level::TileType::Water);

	// Player can only move in water
	return tiles.find(tile) != tiles.end();
}
