#pragma once
#include <format>

namespace acp
{
	template<class T>
	struct Vec3
	{
		T x, y, z;

		Vec3 operator+(const Vec3& rhs) const
		{
			return { static_cast<T>(x + rhs.x), static_cast<T>(y + rhs.y), static_cast<T>(z + rhs.z) };
		}

		Vec3 operator+(const T& rhs) const
		{
			return { static_cast<T>(x + rhs), static_cast<T>(y + rhs), static_cast<T>(z + rhs) };
		}

		Vec3 operator-(const Vec3& rhs) const
		{
			return { x - rhs.x, y - rhs.y, z - rhs.z };
		}

		Vec3 operator-(const T& rhs) const
		{
			return { x - rhs, y - rhs, z - rhs };
		}

		Vec3 operator*(const Vec3& rhs) const
		{
			return { static_cast<T>(x * rhs.x), static_cast<T>(y * rhs.y), static_cast<T>(z * rhs.z) };
		}

		Vec3 operator*(const T& rhs) const
		{
			return { static_cast<T>(x * rhs), static_cast<T>(y * rhs), static_cast<T>(z * rhs) };
		}

		Vec3 operator/(const Vec3& rhs) const
		{
			return { x / rhs.x, y / rhs.y, z / rhs.z };
		}

		Vec3 operator/(const T& rhs) const
		{
			return { x / rhs, y / rhs, z / rhs };
		}

		bool operator<(const Vec3& rhs) const
		{
			return x < rhs.x && y < rhs.y && z < rhs.z;
		}

		bool operator<=(const Vec3& rhs) const
		{
			return x <= rhs.x && y <= rhs.y && z <= rhs.z;
		}

		bool operator>(const Vec3& rhs) const
		{
			return x > rhs.x && y > rhs.y && z > rhs.z;
		}

		bool operator>=(const Vec3& rhs) const
		{
			return x >= rhs.x && y >= rhs.y && z >= rhs.z;
		}

		bool operator==(const Vec3& rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}

		bool operator!=(const Vec3& rhs)
		{
			return !(*this == rhs);
		}

		std::string toString() const
		{
			return std::format("{}:{}:{}", x, y, z);
		}


		template<class From>
		static Vec3 cast(Vec3<From> vec)
		{
			return { static_cast<T>(vec.x), static_cast<T>(vec.y), static_cast<T>(vec.z) };
		}
	};

	typedef Vec3<short> Vec3s;
	typedef Vec3<int> Vec3i;
	typedef Vec3<float> Vec3f;
	typedef Vec3<double> Vec3d;
}
