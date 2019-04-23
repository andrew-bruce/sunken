#include "cmp_sound.hh"

#include <resources.hh>

// Class overrides
CmpSound::CmpSound(Entity* const p, const std::string& string)
: Component(p),
  sound_(nullptr)
{
	load(string);
}



// Logic
void CmpSound::update(const float& delta_time)
{}

void CmpSound::render()
{}



// Loading
void CmpSound::load(const std::string& string)
{
	sound_ = resources::get<sf::Sound>(string);
	if (!sound_)
		return;
}

bool CmpSound::loaded()
{
	return sound_;
}



// Sound
sf::Sound* CmpSound::sound() const
{
	return sound_;
}
