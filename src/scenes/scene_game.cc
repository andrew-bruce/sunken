#include "scene_game.hh"

#include <iostream>

#include <renderer.hh>
#include <level_loader.hh>
#include <engine.hh>

#include "../components/cmp_camera.hh"
#include "../components/cmp_combat_player.hh"
#include "../components/cmp_movement_player.hh"
#include "../components/cmp_shape.hh"
#include "../components/cmp_movement_submarine.hh"
#include "../components/cmp_combat_enemy.hh"
#include "../components/cmp_pickup_ammo.hh"
#include "../components/cmp_pickup_health.hh"
#include "../components/cmp_health_player.hh"
#include "../components/cmp_health_enemy.hh"

void SceneGame::load()
{
	level::load("res/levels/example.txt", 64.0f);

	// Player
	{
		const auto tiles    = level::find_tiles(level::Tile::Player);
		const auto position = level::tile_position(tiles[rand() % tiles.size()]);
		const auto size     = sf::Vector2f(level::tile_size(), level::tile_size()) / 8.0f;

		auto p = make_entity();
		p->move_to(position);
		p->add_tag("player");

		auto s = p->add_component<CmpShape>();
		s->use_shape<sf::RectangleShape>(size);
		s->shape().setOrigin(size / 2.0f);
		s->shape().setFillColor(sf::Color::Yellow);

		p->add_component<CmpCamera>();
		p->add_component<CmpCombatPlayer>();
		p->add_component<CmpMovementPlayer>();
		p->add_component<CmpHealthPlayer>();
	}

	// Enemy submarines
	{
		for (const auto tile : level::find_tiles(level::Tile::Submarine))
		{
			const auto position = level::tile_position(tile);
			const auto size     = sf::Vector2f(level::tile_size(), level::tile_size()) / 8.0f;

			auto e = make_entity();
			e->move_to(position);

			auto s = e->add_component<CmpShape>();
			s->use_shape<sf::RectangleShape>(size);
			s->shape().setOrigin(size / 2.0f);
			s->shape().setFillColor(sf::Color::Blue);

			e->add_component<CmpMovementSubmarine>();
			e->add_component<CmpCombatEnemy>();
			e->add_component<CmpHealthEnemy>();
		}
	}

	// Pickups
	{
		for (const auto t : level::find_tiles(level::Tile::Ammo))
		{
			sf::Vector2f position = level::tile_position(t);

			auto e = make_entity();
			e->move_to(position);

			e->add_component<CmpPickupAmmo>();
		}

		for (const auto t : level::find_tiles(level::Tile::Health))
		{
			sf::Vector2f position = level::tile_position(t);

			auto e = make_entity();
			e->move_to(position);

			e->add_component<CmpPickupHealth>();
		}
	}

	//	std::this_thread::sleep_for(std::chrono::milliseconds(4444));
	loaded(true);
}

void SceneGame::unload()
{
	level::unload();
	Scene::unload();
}



// Logic
void SceneGame::update(const float& delta_time)
{
	Scene::update(delta_time);
}

void SceneGame::render()
{
	renderer::target(nullptr);

	level::render();
	entities_.render();

	renderer::render();
	renderer::draw();
}
