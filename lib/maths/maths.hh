#pragma once

#include <cmath>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <vector>

#include <SFML/System.hpp>

namespace sf
{
	// Type definition
	typedef Vector2<std::size_t> Vector2ul;

	// Operators
	template <typename T>
	Vector2<T> operator*(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left.x * right.x, left.y * right.y);
	}

	// Cast
	template <typename T, typename U>
	Vector2<T> cast(const Vector2<U>& vector)
	{
		return Vector2<T>(static_cast<T>(vector.x), static_cast<T>(vector.y));
	}

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
		const double l = length(vector);
		if (l == 0.0) return vector;
		return cast<T>(cast<double>(vector) / l);
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
		const double theta = deg_to_rad(degrees);
		const double c     = cos(theta);
		const double s     = sin(theta);

		return Vector2<T>(
			vector.x * c - vector.y * s,
			vector.x * s + vector.y * c);
	}

	// Output stream operator
	template <typename T>
	std::ostream& operator<<(std::ostream& output, const Vector2<T>& vector)
	{
		output << '(' << vector.x << ',' << vector.y << ')';
		return output;
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	os << "vec[";
	for (const T& i : v)
		os << i << ',';
	os << ']';
	return os;
}

template <typename T>
std::string to_decimal_place(const unsigned& dp, const T& i)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(dp) << i;
	return stream.str();
}
