#include "scene_game.hh"

#include <iostream>

#include <renderer.hh>
#include <level_loader.hh>
#include <engine.hh>

#include "../sunken.hh"
#include "../components/cmp_camera.hh"
#include "../components/cmp_combat_enemy.hh"
#include "../components/cmp_combat_player.hh"
#include "../components/cmp_health_enemy.hh"
#include "../components/cmp_health_player.hh"
#include "../components/cmp_movement_battleship.hh"
#include "../components/cmp_movement_player.hh"
#include "../components/cmp_movement_submarine.hh"
#include "../components/cmp_music.hh"
#include "../components/cmp_pickup_ammo.hh"
#include "../components/cmp_pickup_health.hh"

#include "../components/cmp_health_player.hh"
#include "../components/cmp_health_enemy.hh"
#include "../components/cmp_movement_battleship.hh"
#include "../components/cmp_combat_battleship.hh"

#include "../components/cmp_shape.hh"
#include "../components/cmp_sprite.hh"
#include "../components/cmp_sonar.hh"
#include "../components/cmp_sound.hh"
#include "../components/cmp_text.hh"

sf::Texture player_texture;
sf::Texture enemy_texture;
sf::Texture battleship_texture;

void SceneGame::load()
{
	level::load("res/levels/level.txt", 64.0f);

	//Player sprite
	{
		const auto tiles = level::find_tiles(level::Tile::Player);
		const auto position = level::tile_position(tiles[rand() % tiles.size()]);

		auto p = make_entity();
		p->move_to(position);
		p->add_tag("player");

		
		if (!player_texture.loadFromFile("res/img/sub-right.png"))
			std::cout << "Sprite load failed";

		auto s = p->add_component<CmpSprite>();
		s->use_sprite<sf::Sprite>();
		s->sprite().setTexture(player_texture);

		// Gets size of texture divided by 10 to account for scaling
		const auto size = sf::Vector2f(s->sprite().getLocalBounds().width, s->sprite().getLocalBounds().height);

		s->sprite().setScale(sf::Vector2f(0.1f, 0.1f));
		s->sprite().setOrigin(size / 2.f);

		auto c = p->add_component<CmpCamera>();
		c->zoom = level::tile_size() * 4.0f;

		p->add_component<CmpCombatPlayer>();
		p->add_component<CmpMovementPlayer>();
		p->add_component<CmpHealthPlayer>();
	}

	// Enemy submarines
	{
		for (const auto tile : level::find_tiles(level::Tile::Submarine))
		{
			const auto position = level::tile_position(tile);

			auto e = make_entity();
			e->move_to(position);

			if (!enemy_texture.loadFromFile("res/img/sub-left.png"))
				std::cout << "Sprite load failed";

			auto s = e->add_component<CmpSprite>();
			s->use_sprite<sf::Sprite>();
			s->sprite().setTexture(enemy_texture);

			// Gets size of texture divided by 10 to account for scaling
			const auto size = sf::Vector2f(s->sprite().getLocalBounds().width, s->sprite().getLocalBounds().height);

			s->sprite().setOrigin(size / 2.f);
			s->sprite().setScale(sf::Vector2f(0.1f, 0.1f));

			e->add_component<CmpMovementSubmarine>();
			e->add_component<CmpCombatEnemy>();
			e->add_component<CmpHealthEnemy>();
			e->add_tag("enemy");
			e->add_tag("submarine");
		}
	}

	// Enemy battleships
	{
		for (const auto tile : level::find_tiles(level::Tile::Battleship))
		{
			const auto position = level::tile_position(tile);
			level::Tile t = level::tile_at(position);

			auto e = make_entity();

			battleship_texture.loadFromFile("res/img/ship-left.png");

			auto s = e->add_component<CmpSprite>();

			s->use_sprite<sf::Sprite>();
			s->sprite().setTexture(battleship_texture);

			// Gets size of texture divided by 10 to account for scaling
			const auto size = sf::Vector2f(s->sprite().getLocalBounds().width, s->sprite().getLocalBounds().height);

			s->sprite().setOrigin(size / 2.f);
			s->sprite().setScale(sf::Vector2f(0.1f, 0.1f));
			e->move_to(sf::Vector2f(position.x, position.y + s->sprite().getTexture()->getSize().y / 14.7f));

			std::cout << s->sprite().getTexture()->getSize().y << std::endl;

			e->add_component<CmpMovementBattleship>();
			e->add_component<CmpCombatBattleship>();
			e->add_component<CmpHealthEnemy>();
			e->add_tag("enemy");
			e->add_tag("battleship");
		}
	}

	// Objective
	{
		for (const auto tile : level::find_tiles(level::Tile::Objective))
		{
			const auto position = level::tile_position(tile);
			const auto size = sf::Vector2f(35.f, 35.f);

			auto e = make_entity();
			e->move_to(position);

			auto s = e->add_component<CmpShape>();
			s->use_shape<sf::RectangleShape>(size);
			s->shape().setFillColor(sf::Color(232, 232, 232));

			e->add_component<CmpCombatEnemy>();
			e->add_component<CmpHealthEnemy>();
			e->add_tag("objective");
		}
	}

	// Pickups
	{
		for (const auto t : level::find_tiles(level::Tile::Ammo))
		{
			sf::Vector2f position = level::tile_position(t);

			auto e = make_entity();
			e->move_to(position);
			e->add_tag("pickup");

			e->add_component<CmpPickupAmmo>();
		}

		for (const auto t : level::find_tiles(level::Tile::Health))
		{
			sf::Vector2f position = level::tile_position(t);

			auto e = make_entity();
			e->move_to(position);
			e->add_tag("pickup");

			e->add_component<CmpPickupHealth>();
		}
	}

	// HUD
	{
		auto e = make_entity();
		e->add_tag("hud");

		auto t = e->add_component<CmpText>();
		t->text.setFillColor(sf::Color::White);
		t->text.setOutlineColor(sf::Color::Black);
		t->text.setOutlineThickness(2.0f);
	}

	// Victory
	{
		auto e = make_entity();
		e->add_tag("endcard");

		auto t = e->add_component<CmpText>();
		t->text.setFillColor(sf::Color::White);
		t->text.setOutlineColor(sf::Color::Black);
		t->text.setOutlineThickness(2.0f);

		e->visible(false);
	}

	// Music
	{
		auto music = make_entity();
		music->add_tag("music");

		auto m = music->add_component<CmpMusic>("unseen-horrors.ogg");
		if (m->loaded())
		{
			m->music()->setVolume(25);
			m->music()->play();
		}
		else
			music->delete_please();
	}

	// Sonar entity
	{
		auto e = make_entity();
		e->add_tag("sonar");

		auto s = e->add_component<CmpShape>();
		s->use_shape<sf::CircleShape>(0.0f, 64);
		s->shape().setFillColor(sf::Color::Transparent);
		s->shape().setOutlineThickness(1.0f);

		auto p = e->add_component<CmpSound>("sonar.ogg");
		p->sound().setVolume(50);

		e->add_component<CmpSonar>();
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
	if (engine::keyboard[sf::Keyboard::Escape])
		return engine::change_scene(&scene_menu);

	// HUD
	{
		auto hud = entities_.find("hud").front();
		if (!entities_.find("player").empty())
		{
			auto text = hud->compatible_components<CmpText>().front();

			auto player = entities_.find("player").front();
			auto health = player->compatible_components<CmpHealthPlayer>().front();
			auto ammo = player->compatible_components<CmpCombatPlayer>().front();
			
			std::string output = "Health: ";
			output += to_decimal_place(0, health->health());
			output += "\tAmmo: ";
			output += std::to_string(ammo->ammo());
			text->text.setString(output);

			auto window = engine::window();
			auto view = window->getView();
			auto top_left = view.getCenter() - view.getSize() / 2.0f;

			text->text.setScale(view.getSize() / window->getSize());
			hud->move_to(top_left);
		}
	}

	// End card
	{
		auto window = engine::window();
		auto view = window->getView();

		// Defeat
		if (!entities_.find("player").front()->is_visible())
		{
			for (auto& e : entities_.find("enemy"))
				e->delete_please();


			auto d = entities_.find("endcard").front();
			d->visible(true);

			auto t = d->compatible_components<CmpText>().front();
			t->text.setString("Defeat");
			t->text.setOrigin(t->text.getLocalBounds().width / 2, t->text.getLocalBounds().height / 2);
			t->text.setScale(view.getSize() / window->getSize());

			d->move_to(view.getCenter());

			static float pause = 2.5f;
			pause -= delta_time;
			if (pause < 0.0f)
				return engine::change_scene(&scene_menu);
		}

		// Victory
		else if (entities_.find("objective").empty())
		{
			for (auto& e : entities_.find("enemy"))
				e->delete_please();

			auto v = entities_.find("endcard").front();
			v->visible(true);

			auto t = v->compatible_components<CmpText>().front();
			t->text.setString("Victory");
			t->text.setOrigin(t->text.getLocalBounds().width / 2, t->text.getLocalBounds().height / 2);
			t->text.setScale(view.getSize() / window->getSize());

			v->move_to(view.getCenter());

			static float pause = 2.5f;
			pause -= delta_time;
			if (pause < 0.0f)
				return engine::change_scene(&scene_menu);
		}
	}

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
