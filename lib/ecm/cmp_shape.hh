#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "ecm.hh"

struct CmpShape : Component
{
protected:
	std::unique_ptr<sf::Shape> shape_;

public:
	// Class overrides
	CmpShape() = delete;
	explicit CmpShape(Entity* p);
	~CmpShape() = default;

	// Logic
	void update(const float& delta_time) override;
	void render() override;

	// Reference to shape
	sf::Shape& shape() const;

	// Replaces shape used
	template <typename T, typename... Targs>
	void use_shape(Targs... params) {
		shape_.reset(new T(params...));
	}
};

