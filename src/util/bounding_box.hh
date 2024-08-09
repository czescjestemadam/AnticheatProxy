#pragma once
#include "vec3.hh"

namespace acp
{
	template<class T>
	struct BoundingBox
	{
		Vec3<T> min, max;

		BoundingBox(Vec3<T> min, Vec3<T> max)
			: min({ std::min(min.x, max.x), std::min(min.y, max.y), std::min(min.z, max.z) }),
			  max({ std::max(min.x, max.x), std::max(min.y, max.y), std::max(min.z, max.z) })
		{
		}

		bool contains(const Vec3<T>& vec) const
		{
			return min <= vec && vec <= max;
		}

		bool contains(const BoundingBox<T>& box) const
		{
			return contains(box.min) && contains(box.max);
		}

		bool intersects(const BoundingBox<T>& box) const
		{
			return contains(box.min) || contains(box.max);
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
