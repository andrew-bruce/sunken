#include "cmp_sound_temp.hh"

// Class overrides
CmpSoundTemp::CmpSoundTemp(Entity* const p, const std::string& string)
: CmpSound(p, string)
{
	load(string);
}



// Logic
void CmpSoundTemp::update(const float& delta_time)
{
	if (sound_.getStatus() == sf::Sound::Stopped)
		parent_->delete_please();
}

void CmpSoundTemp::render()
{}
