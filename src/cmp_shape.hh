#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include <ecm.hh>

struct CmpShape : Component {
	CmpShape() = delete;
	explicit CmpShape(Entity* p);
	~CmpShape() = default;

	void update(const float& delta_time) override;
	void render() override;

	const sf::Shape& shape() const;

	template <typename T, typename... Targs>
	void use_shape(Targs... params) {
		shape_.reset(new T(params...));
	}

protected:
	std::unique_ptr<sf::Shape> shape_;
};