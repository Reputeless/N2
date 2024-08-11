#pragma once
#include <memory> // std::shared_ptr
#include <string_view> // std::string_view
#include <string> // std::string
#include "Common.hpp"

namespace seccamp
{
	/// @brief テキストファイルを読み込むクラス
	class TextFileReader
	{
	public:

		/// @brief デフォルトコンストラクタ
		[[nodiscard]]
		TextFileReader();

		/// @brief ファイルをオープンします。
		/// @param path ファイルパス
		[[nodiscard]]
		explicit TextFileReader(std::string_view path);

		/// @brief ファイルがオープンされているかを返します。
		/// @return オープンされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isOpen() const noexcept;

		/// @brief ファイルがオープンされているかを返します。
		/// @return オープンされている場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief ファイルをオープンします。すでにオープンされている場合はクローズしてから再オープンします。
		/// @param path ファイルパス
		/// @return オープンに成功した場合 true, それ以外の場合は false
		[[nodiscard]]
		bool open(std::string_view path);

		/// @brief ファイルをクローズします。
		void close();

		/// @brief ファイルから 1 行読み込みます。
		/// @param line 読み込んだ文字列の格納先
		/// @return 読み込みに成功した場合 true, それ以外の場合は false
		bool readLine(std::string& line);

		/// @brief ファイルの絶対パスを返します。
		/// @return ファイルの絶対パス。ファイルがオープンされていない場合は空文字列
		[[nodiscard]]
		const std::string& fullPath() const noexcept;

	private:

		class Impl;

		std::shared_ptr<Impl> m_pImpl;
	};
}
