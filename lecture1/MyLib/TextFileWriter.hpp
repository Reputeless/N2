#pragma once
#include <memory> // std::shared_ptr
#include <string_view> // std::string_view
#include <format> // std::format
#include "Common.hpp"

namespace seccamp
{
	/// @brief テキストファイルを書き出すクラス
	class TextFileWriter
	{
	public:

		/// @brief デフォルトコンストラクタ
		[[nodiscard]]
		TextFileWriter();

		/// @brief ファイルを作成してオープンします。
		/// @param path ファイルパス
		[[nodiscard]]
		explicit TextFileWriter(std::string_view path);

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

		/// @brief ファイルに文字列を書き込みます。
		/// @param s 書き込む文字列
		void write(std::string_view s);

		/// @brief ファイルに文字列を書き込み、CRLF（\r\n）を追加します。
		/// @param s 書き込む文字列
		void writeln(std::string_view s);

		/// @brief ファイルに文字列を書き込みます。
		/// @tparam Types 書き込むデータの型
		/// @param fmt 書式文字列
		/// @param args 書き込むデータ
		template <class... Types>
		void write(std::format_string<Types...> fmt, Types&&... args)
		{
			write(std::format(fmt, std::forward<Types>(args)...));
		}

		/// @brief ファイルに文字列を書き込み、CRLF（\r\n）を追加します。
		/// @tparam Types 書き込むデータの型
		/// @param fmt 書式文字列
		/// @param args 書き込むデータ
		template <class... Types>
		void writeln(std::format_string<Types...> fmt, Types&&... args)
		{
			writeln(std::format(fmt, std::forward<Types>(args)...));
		}

		/// @brief ファイルの絶対パスを返します。
		/// @return ファイルの絶対パス。ファイルがオープンされていない場合は空文字列
		[[nodiscard]]
		const std::string& fullPath() const noexcept;

	private:

		class Impl;

		std::shared_ptr<Impl> m_pImpl;
	};
}
