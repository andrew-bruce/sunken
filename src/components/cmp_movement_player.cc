#include "cmp_movement_player.hh"

#include <maths.hh>
#include <engine.hh>
#include <level_loader.hh>

// Class overrides
CmpMovementPlayer::CmpMovementPlayer(Entity* p) : CmpMovement(p) {}

// Logic
void CmpMovementPlayer::update(const float& delta_time)
{
	// Input decides direction vector
	sf::Vector2f movement(0.0f, 0.0f);

	// Prevents player from going above surface of water
	if(level::tile_at(parent_->position()) != level::Tile::Air)
		if (engine::keyboard[sf::Keyboard::W])
			--movement.y;

		if (engine::keyboard[sf::Keyboard::A])
			--movement.x;
		if (engine::keyboard[sf::Keyboard::D])
			++movement.x;
		if (engine::keyboard[sf::Keyboard::S])
			++movement.y;

	// Normalise movement vector
	movement  = sf::normalise(movement);
	movement *= speed_ * delta_time;

	// Move player
	move(movement);
}

void CmpMovementPlayer::render() {}

