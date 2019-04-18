#include "scene_test.hh"

#include <level_loader.hh>
#include <iostream>

#include "../components/cmp_shape.hh"
#include "../components/cmp_movement_player.hh"
#include "../components/cmp_combat_player.hh"
#include "../components/cmp_movement_enemy.hh"
#include "../components/cmp_combat_enemy.hh"
#include "../components/cmp_pickup_ammo.hh"
#include "../components/cmp_pickup_health.hh"

void SceneTest::load()
{
	level::load("res/levels/example.txt", 64.0f);

	{
		sf::Vector2f position =
			level::tile_position(level::find_tiles(
				level::Tile::Player).front())
			+ sf::Vector2f(level::tile_size(), level::tile_size())
			/ 2.0f;
		sf::Vector2f size = sf::Vector2f(level::tile_size(), level::tile_size()) / 8.0f;

		// Add player //
		auto p = make_entity();
		p->move_to(position);
		p->add_tag("player");
#
		auto s = p->add_component<CmpShape>();
		s->use_shape<sf::RectangleShape>(size);
		s->shape().setOrigin(size / 2.0f);
		s->shape().setFillColor(sf::Color::Yellow);

		p->add_component<CmpMovementPlayer>();
		p->add_component<CmpCombatPlayer>();
		// Add player //

		// Add enemy //
		sf::Vector2f enemy_position =
			level::tile_position(level::find_tiles(
				level::Tile::Submarine).front())
			+ sf::Vector2f(level::tile_size(), level::tile_size())
			/ 2.0f;

		auto e = make_entity();
		e->move_to(enemy_position);

		auto es = e->add_component<CmpShape>();
		es->use_shape<sf::RectangleShape>(size);
		es->shape().setOrigin(size / 2.0f);
		es->shape().setFillColor(sf::Color::Blue);

		e->add_component<CmpMovementEnemy>();
		e->add_component<CmpCombatEnemy>();
		// Add enemy //

		// Spawn ammo pickups //
		for (auto t : level::find_tiles(level::Tile::Ammo))
		{
			sf::Vector2f pickup_position = level::tile_position(t) + sf::Vector2f(level::tile_size(), level::tile_size()) / 2.0f;
			auto e = make_entity();
			e->move_to(pickup_position);
			e->add_component <CmpPickupAmmo>();
		}
		// Spawn ammo pickups //

		// Spawn health pickups //
		for (auto t : level::find_tiles(level::Tile::Health))
		{
			sf::Vector2f pickup_position = level::tile_position(t) + sf::Vector2f(level::tile_size(), level::tile_size()) / 2.0f;
			auto e = make_entity();
			e->move_to(pickup_position);
			e->add_component <CmpPickupHealth>();
		}
		// Spawn health pickups //
	}

	//	std::this_thread::sleep_for(std::chrono::milliseconds(4444));
	loaded(true);
}

void SceneTest::update(const float& delta_time)
{
	Scene::update(delta_time);
}

void SceneTest::render()
{
	level::render();
	Scene::render();
}
