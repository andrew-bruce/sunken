#pragma once

#include <string>

#include <SFML/Audio/Music.hpp>

#include <ecm.hh>

struct CmpMusic : Component
{
private:
	sf::Music* music_;

public:
	// Class overrides
	CmpMusic() = delete;
	explicit CmpMusic(Entity* const p, const std::string& string = "");
	~CmpMusic() override = default;

	// Logic
	void update(const float& delta_time) override;
	void render() override;

	// Loading
	void load(const std::string& string = "");
	bool loaded();

	// Music
	sf::Music* music() const;
};
