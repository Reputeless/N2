#pragma once
#include <string_view> // std::string_view, std::u32string_view
#include <string> // std::string, std::u32string
#include "Common.hpp"

namespace seccamp
{
	namespace Unicode
	{
		/// @brief UTF-32 文字列を UTF-8 文字列に変換します。
		/// @param utf32 UTF-32 文字列
		/// @return UTF-8 文字列
		[[nodiscard]]
		std::string ToUTF8(std::u32string_view utf32);

		/// @brief UTF-8 文字列を UTF-32 文字列に変換します。
		/// @param utf8 UTF-8 文字列
		/// @return UTF-32 文字列
		[[nodiscard]]
		std::u32string ToUTF32(std::string_view utf8);
	}
}
