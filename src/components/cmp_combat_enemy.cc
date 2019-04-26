#include "cmp_combat_enemy.hh"

#include <iostream>

#include <maths.hh>
#include <level_loader.hh>
#include <scene.hh>

CmpCombatEnemy::CmpCombatEnemy(Entity* const p)
: CmpCombat(p)
{
	ammo_ = 1000;
}

void CmpCombatEnemy::update(const float & delta_time)
{
	// Get player
	if (parent_->scene->entities().find("player").empty())
		return;

	const Entity* player = parent_->scene->entities().find("player").front();

	// Get vector between entity and player
	const sf::Vector2f vector = player->position() - parent_->position();

	// Get distance between enemy and player
	float distance = sf::length2(vector);

	// If the player is close enough, fire in their direction (squared length of 200)
	if (distance <= 4000)
		fire(sf::normalise(vector), "enemy_torpedo");

	CmpCombat::update(delta_time);
}

void CmpCombatEnemy::render() {}
