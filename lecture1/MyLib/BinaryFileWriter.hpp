#pragma once
#include <memory> // std::shared_ptr, std::addressof
#include <string_view> // std::string_view
#include <string> // std::string
#include <type_traits> // std::is_trivially_copyable_v
#include "Common.hpp"

namespace seccamp
{
	/// @brief バイナリファイルを書き出すクラス
	class BinaryFileWriter
	{
	public:

		/// @brief デフォルトコンストラクタ
		[[nodiscard]]
		BinaryFileWriter();
		
		/// @brief ファイルを作成してオープンします。
		/// @param path ファイルパス
		[[nodiscard]]
		explicit BinaryFileWriter(std::string_view path);

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

		/// @brief ファイルにデータを書き込みます。
		/// @param data 書き込むデータ
		/// @param size データのサイズ（バイト）
		void write(const void* data, size_t size);

		/// @brief ファイルにデータを書き込みます。
		/// @tparam T 書き込むデータの型
		/// @param data 書き込むデータ
		template <class T>
			requires std::is_trivially_copyable_v<T>
		void write(const T& data)
		{
			write(std::addressof(data), sizeof(T));
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
