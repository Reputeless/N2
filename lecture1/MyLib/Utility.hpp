#pragma once
#include <concepts> // std::integral
#include <string_view> // std::string_view
#include <string> // std::string
#include "Common.hpp"

namespace seccamp
{
	/// @brief 整数 n が偶数であるかを返します。
	/// @param n 調べる整数
	/// @return n が偶数の場合 true、そうでない場合 false
	[[nodiscard]]
	constexpr bool IsEven(std::integral auto n) noexcept
	{
		return ((n % 2) == 0);
	}

	/// @brief 整数 n が奇数であるかを返します。
	/// @param n 調べる整数
	/// @return n が奇数の場合 true、そうでない場合 false
	[[nodiscard]]
	constexpr bool IsOdd(std::integral auto n) noexcept
	{
		return ((n % 2) != 0);
	}

	/// @brief 整数 n が範囲 [min, max] に含まれるかを返します。
	/// @param n 調べる整数
	/// @param min 最小値
	/// @param max 最大値
	/// @return n が範囲 [min, max] に含まれる場合 true、そうでない場合は false
	[[nodiscard]]
	constexpr bool InRange(std::integral auto n, std::integral auto min, std::integral auto max) noexcept
	{
		return ((min <= n) && (n <= max));
	}

	/// @brief 文字列中の英字を小文字に変換します。
	/// @param s 変換する文字列
	/// @return 文字中の英字を小文字に変換した新しい文字列
	[[nodiscard]]
	std::string ToLower(std::string_view s);

	/// @brief 文字列中の英字を大文字に変換します。
	/// @param s 変換する文字列
	/// @return 文字中の英字を大文字に変換した新しい文字列
	[[nodiscard]]
	std::string ToUpper(std::string_view s);

	/// @brief 指定した時間（ミリ秒）スリープします。
	/// @param milliseconds スリープする時間（ミリ秒）
	void Sleep(int32 milliseconds);
}
