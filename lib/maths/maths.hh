#pragma once

#include <cmath>
#include <ostream>

#include <SFML/System.hpp>



namespace sf
{
	// TYPE DEFINITION
	typedef Vector2<std::size_t> Vector2ul;

	// SQUARED LENGTH
	template <typename T>
	T length2(const Vector2<T>& vector)
	{
		return
			vector.x * vector.x +
			vector.y * vector.y;
	}

	// LENGTH
	template <typename T>
	double length(const Vector2<T>& vector)
	{
		return sqrt(static_cast<double>(
			length2(vector)));
	}

	// NORMALISE
	template <typename T>
	Vector2<T> normalise(const Vector2<T>& vector)
	{
		const double l(length(vector));
		if (l == 0.0)
			return vector;

		Vector2<T> output;
		output.x = static_cast<T>(static_cast<double>(
			vector.x) / l);
		output.y = static_cast<T>(static_cast<double>(
			vector.y) / l);

		return output;
	}

	// CAST
	template <typename T, typename U>
	Vector2<T> cast(const Vector2<U>& vector)
	{
		return Vector2<T>(static_cast<T>(
			vector.x), static_cast<T>(
			vector.y));
	}

	// DEGREES TO RADIANS
	static double deg2rad(const double& degrees)
	{
		return degrees / 180.0 * 3.141592653589793238462643383279502884L;
	}

	// ROTATE VECTOR BY DEGREES
	template <typename T>
	Vector2<T> rotate(
		const Vector2<T>& vector,
		const double& degrees)
	{
		const double theta(deg2rad(degrees));
		const double c = cos(theta);
		const double s = sin(theta);

		return Vector2<T>(
			vector.x * c - vector.y * s,
			vector.x * s + vector.y * c);
	}

	// OUTPUT STREAM OPERATOR
	template <typename T>
	std::ostream& operator<<(
		std::ostream& output,
		const Vector2<T>& vector)
	{
		output << '(' <<
			vector.x << ", " <<
			vector.y << ')';
		return output;
	}
};
