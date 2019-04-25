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
	// Get player
	const Entity* player = parent_->scene->entities().find("player").front();
	float x_diff = player->position().x - parent_->position().x;
	float y_diff = player->position().y - parent_->position().y;

	std::cout << y_diff << std::endl;

	if (x_diff >= -50 && x_diff <= 50 && y_diff < 150.f)
		fire(sf::Vector2f(0.f, 1.f), "battleship_bomb");

	CmpCombat::update(delta_time);
}

void CmpCombatBattleship::render() {}
