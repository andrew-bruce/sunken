#include "resources.hh"

namespace resources
{
	template <>
	std::unique_ptr<sf::Font> load(const std::string& name)
	{
		auto f = std::make_unique<sf::Font>();
		if (!f->loadFromFile("res/fonts/" + name))
			return nullptr;
		return std::move(f);
	}

	template <>
	std::unique_ptr<sf::Texture> load(const std::string& name)
	{
		auto t = std::make_unique<sf::Texture>();
		if (!t->loadFromFile("res/textures/" + name))
			return nullptr;
		return std::move(t);
	}

#ifdef SOUND

	template <>
	std::unique_ptr<sf::SoundBuffer> load(const std::string& name)
	{
		auto s = std::make_unique<sf::SoundBuffer>();
		if (!s->loadFromFile("res/sound/" + name))
			return nullptr;
		return std::move(s);
	}

	template <>
	std::unique_ptr<sf::Music> load(const std::string& name)
	{
		auto m = std::make_unique<sf::Music>();
		if (!m->openFromFile("res/music/" + name))
			return nullptr;
		return std::move(m);
	}

#endif
};
