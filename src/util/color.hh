#pragma once
#include "types.hh"

#include <format>
#include <string>

namespace acp
{
	template<class T>
	struct Color
	{
		T r, g, b;

		Color() = default;

		Color(T r, T g, T b) : r(r), g(g), b(b)
		{
		}

		Color operator*(T v)
		{
			return { r * v, g * v, b * v };
		}

		std::string toString() const
		{
			return std::format("Color[{}, {}, {}]", r, g, b);
		}
	};

	typedef Color<byte_t> ColorB;
	typedef Color<float> ColorF;

	inline ColorB toColorB(const ColorF& color)
	{
		return { static_cast<byte_t>(color.r / 1), static_cast<byte_t>(color.g / 1), static_cast<byte_t>(color.b / 1) };
	}

	inline ColorF toColorF(const ColorB& color)
	{
		return { color.r / 255.f, color.g / 255.f, color.b / 255.f };
	}

	namespace colors
	{
		const static ColorB BLACK = { 0, 0, 0 };
		const static ColorB WHITE = { 255, 255, 255 };
		const static ColorB RED = { 255, 0, 0 };
		const static ColorB GREEN = { 0, 255, 0 };
		const static ColorB BLUE = { 0, 0, 255 };
	}
}
