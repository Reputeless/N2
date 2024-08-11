#pragma once
#include <string_view> // std::string_view
#include <string> // std::string
#include "Common.hpp"

namespace seccamp
{
	namespace FileSystem
	{
		/// @brief ファイルパスを絶対パスに変換します。
		/// @param path ファイルパス
		/// @return 絶対パス
		[[nodiscard]]
		std::string FullPath(std::string_view path);

		/// @brief ファイルパスから拡張子を取得します。（例: ".txt", ".JPEG"）
		/// @param path ファイルパス
		/// @return 拡張子。拡張子が存在しない場合は空文字列
		[[nodiscard]]
		std::string Extension(std::string_view path);
	}
}
