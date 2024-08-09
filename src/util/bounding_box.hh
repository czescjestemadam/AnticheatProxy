#pragma once
#include "vec3.hh"

namespace acp
{
	template<class T>
	struct BoundingBox
	{
		Vec3<T> min, max;

		bool contains(const Vec3<T>& vec)
		{
			return min <= vec && vec <= max;
		}

		static BoundingBox from(Vec3<T> center, Vec3<T> size)
		{
			const Vec3<T> halfSize = size / 2;
			return { center - halfSize, center + halfSize };
		}

		static BoundingBox fromPos(Vec3<T> pos, Vec3<T> size)
		{
			const Vec3<T> halfSize = size / 2;
			const Vec3<T> min = { pos.x - halfSize.x, pos.y, pos.z - halfSize.z };
			return { min, min + size };
		}
	};

	typedef BoundingBox<short> BoundingBoxS;
	typedef BoundingBox<int> BoundingBoxI;
	typedef BoundingBox<float> BoundingBoxF;
	typedef BoundingBox<double> BoundingBoxD;
}
