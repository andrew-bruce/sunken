#include "cmp_combat_player.hh"

#include <SFML/Window.hpp>

#include <engine.hh>

// Class overrides
CmpCombatPlayer::CmpCombatPlayer(Entity* const p)
: CmpCombat(p)
{}



// Logic
void CmpCombatPlayer::update(const float & delta_time)
{
	// If fire button pressed
	if (engine::mouse[sf::Mouse::Left])
	{
		// Get direction vector to mouse position
		const sf::Vector2f vector = engine::mouse_position - parent_->position();
		fire(sf::normalise(vector));
	}

	CmpCombat::update(delta_time);
}

void CmpCombatPlayer::render()
{}
