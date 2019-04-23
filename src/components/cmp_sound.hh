#pragma once

#include <string>

#include <SFML/Audio/Sound.hpp>

#include <ecm.hh>

struct CmpSound : Component
{
private:
	sf::Sound* sound_;

public:
	// Class overrides
	CmpSound() = delete;
	explicit CmpSound(Entity* const p, const std::string& string = "");
	~CmpSound() override = default;

	// Logic
	void update(const float& delta_time) override;
	void render() override;

	// Loading
	void load(const std::string& string = "");
	bool loaded();

	// Music
	sf::Sound* sound() const;
};
