#include "cmp_music.hh"

#include <resources.hh>

// Class overrides
CmpMusic::CmpMusic(Entity* const p, const std::string& string)
: Component(p),
  music_(nullptr)
{
	load(string);
}



// Logic
void CmpMusic::update(const float& delta_time)
{}

void CmpMusic::render()
{}



// Loading
void CmpMusic::load(const std::string& string)
{
	music_ = resources::get<sf::Music>(string);
	if (!music_)
		return;

	music_->setAttenuation(0);
	music_->setLoop(true);
}

bool CmpMusic::loaded()
{
	return music_;
}



// Music
sf::Music* CmpMusic::music() const
{
	return music_;
}
