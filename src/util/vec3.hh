#pragma once

namespace acp
{
	template<class T>
	struct Vec3
	{
		T x, y, z;

		Vec3 operator+(const Vec3& rhs) const
		{
			return { x + rhs.x, y + rhs.y, z + rhs.z };
		}

		Vec3 operator-(const Vec3& rhs) const
		{
			return { x - rhs.x, y - rhs.y, z - rhs.z };
		}

		Vec3 operator*(const Vec3& rhs) const
		{
			return { x * rhs.x, y * rhs.y, z * rhs.z };
		}

		Vec3 operator/(const Vec3& rhs) const
		{
			return { x / rhs.x, y / rhs.y, z / rhs.z };
		}

		bool operator==(const Vec3& rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}

		bool operator!=(const Vec3& rhs)
		{
			return !(*this == rhs);
		}
	};

	typedef Vec3<short> Vec3s;
	typedef Vec3<int> Vec3i;
	typedef Vec3<float> Vec3f;
	typedef Vec3<double> Vec3d;
}
