#pragma once
#include "vec3.hh"

namespace acp
{
	template<class T>
	struct BoundingBox
	{
		Vec3<T> min, max;

		template<T>
		static BoundingBox from(Vec3<T> center, Vec3<T> size)
		{
			const Vec3<T> halfSize = size / 2;
			return { center - halfSize, center + halfSize };
		}
	};

	typedef BoundingBox<short> BoundingBoxS;
	typedef BoundingBox<int> BoundingBoxI;
	typedef BoundingBox<float> BoundingBoxF;
	typedef BoundingBox<double> BoundingBoxD;
}
