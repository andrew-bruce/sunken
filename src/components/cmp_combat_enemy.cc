#include "cmp_combat_enemy.hh"
#include<maths.hh>
#include <iostream>
#include <level_loader.hh>

CmpCombatEnemy::CmpCombatEnemy(Entity * p) : CmpCombat(p) {
	ammo_ = 1000;
}

void CmpCombatEnemy::update(const float & delta_time)
{
	// Get player
	auto player = parent_->scene->entities().find("player").front();

	// Get player and enemy position
	sf::Vector2f pp = player->position();
	sf::Vector2f ep = parent_->position();

	// Get distance between enemy and player
	float distance = pow(pow(pp.x - ep.x, 2) + pow(pp.y - ep.y, 2), 0.5);

	// If the enemy is close enough to the player, fire in their direction
	if (distance <= 200) 
	{
		auto d = sf::normalise(pp - ep);
		fire(d);
	}

	CmpCombat::update(delta_time);
}

void CmpCombatEnemy::render(){}
