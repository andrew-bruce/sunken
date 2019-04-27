#include "cmp_combat_battleship.hh"

#include <iostream>

#include <maths.hh>
#include <level_loader.hh>
#include <scene.hh>

CmpCombatBattleship::CmpCombatBattleship(Entity* const p)
	: CmpCombat(p)
{
	ammo_ = 1000;
}

void CmpCombatBattleship::update(const float & delta_time)
{
	if (parent_->scene->entities().find("player").empty())
		return;

	// Get player
	const Entity* player = parent_->scene->entities().find("player").front();
	if (!player)
		return;

	const auto diff  = player->position() - parent_->position();
	const auto range = level::tile_size();

	if (diff.x >= -range / 2.0f && diff.x <= range / 2.0f && diff.y < range * 2.5f)
		fire(sf::Vector2f(0.0f, 1.0f), "battleship_bomb");

	CmpCombat::update(delta_time);
}

void CmpCombatBattleship::render() {}
