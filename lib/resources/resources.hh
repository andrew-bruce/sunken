#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include <SFML/Audio.hpp>
#ifdef SOUND
	#include <SFML/Audio/Sound.hpp>
#endif
#include <SFML/Graphics.hpp>

namespace resources
{
	template <typename T>
	std::unique_ptr<T> load(const std::string& name)
	{
		std::cerr << "ERROR resource loader invalid type" << std::endl;
		return nullptr;
	}

	template <>
	std::unique_ptr<sf::Font> load(const std::string& name);

	template <>
	std::unique_ptr<sf::Texture> load(const std::string& name);

	template <>
	std::unique_ptr<sf::SoundBuffer> load(const std::string& name);

	template <>
	std::unique_ptr<sf::Music> load(const std::string& name);

	template <typename T>
	static T* get(const std::string& name)
	{
		static std::map<std::string, std::unique_ptr<T>> things_;

		auto search = things_.find(name);

		if (search != things_.end())
			return search->second.get();

		std::unique_ptr<T> ptr = load<T>(name);
		if (!ptr)
		{
			std::cerr << "ERROR nothing loaded for " << name << std::endl;
			return nullptr;
		}

		things_[name] = std::move(ptr);
		return things_[name].get();
	}
};
