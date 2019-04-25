#include "cmp_sound.hh"

#include <resources.hh>

// Class overrides
CmpSound::CmpSound(Entity* const p, const std::string& string)
: Component(p),
  buffer_(nullptr)
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
	buffer_ = resources::get<sf::SoundBuffer>(string);
	if (!buffer_)
		return;

	sound_.setBuffer(*buffer_);
}

bool CmpSound::loaded() const
{
	return buffer_;
}



// Sound
sf::Sound& CmpSound::sound()
{
	return sound_;
}
