#pragma once

#include <cmath>
#include <ostream>

#include <SFML/System.hpp>

namespace sf
{
	// Type definition
	typedef Vector2<std::size_t> Vector2ul;

	// Squared length
	template <typename T>
	T length2(const Vector2<T>& vector)
	{
		return vector.x * vector.x + vector.y * vector.y;
	}

	// Length
	template <typename T>
	double length(const Vector2<T>& vector)
	{
		return sqrt(static_cast<double>(length2(vector)));
	}

	// Normalise
	template <typename T>
	Vector2<T> normalise(const Vector2<T>& vector)
	{
		const double l(length(vector));
		if (l == 0.0) return vector;

		Vector2<T> output(
			static_cast<T>(static_cast<double>(vector.x) / l),
			static_cast<T>(static_cast<double>(vector.y) / l));

		return output;
	}

	// Cast
	template <typename T, typename U>
	Vector2<T> cast(const Vector2<U>& vector)
	{
		return Vector2<T>(static_cast<T>(vector.x), static_cast<T>(vector.y));
	}

	// Degrees to radians
	static double deg_to_rad(const double& degrees)
	{
		return degrees / 180.0 * 3.141592653589793238462643383279502884L;
	}

	// Rotate vector by degrees
	template <typename T>
	Vector2<T> rotate(const Vector2<T>& vector, const double& degrees)
	{
		const double theta (deg_to_rad(degrees));
		const double c     (cos(theta));
		const double s     (sin(theta));

		return Vector2<T>(
			vector.x * c - vector.y * s,
			vector.x * s + vector.y * c);
	}

	// Output stream operator
	template <typename T>
	std::ostream& operator<<(std::ostream& output, const Vector2<T>& vector)
	{
		output << '(' << vector.x << ", " << vector.y << ')';
		return output;
	}
};

