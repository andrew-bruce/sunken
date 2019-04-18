#include "cmp_combat_player.hh"

#include <engine.hh>
#include <SFML/Window.hpp>

CmpCombatPlayer::CmpCombatPlayer(Entity * p) : CmpCombat(p) {}

void CmpCombatPlayer::update(const float & delta_time)
{
	// If player clicks left mouse
	if (engine::mouse[sf::Mouse::Left])
	{
		// Get mouse position, draw line between player and mouse and fire down that line
		auto m = sf::Mouse::getPosition(engine::window());
		auto d = sf::normalise(sf::cast<float>(m) - parent_->position());

		fire(d);
	}

	CmpCombat::update(delta_time);
}

void CmpCombatPlayer::render() {}
