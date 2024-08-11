#pragma once
#include <memory> // std::shared_ptr, std::addressof
#include <string_view> // std::string_view
#include <string> // std::string
#include <type_traits> // std::is_trivially_copyable_v
#include "Common.hpp"

namespace seccamp
{
	/// @brief バイナリファイルを読み込むクラス
	class BinaryFileReader
	{
	public:

		/// @brief デフォルトコンストラクタ
		[[nodiscard]]
		BinaryFileReader();

		/// @brief ファイルをオープンします。
		/// @param path ファイルパス
		[[nodiscard]]
		explicit BinaryFileReader(std::string_view path);

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

		/// @brief ファイルのサイズ（バイト）を返します。
		/// @return ファイルのサイズ（バイト）。ファイルがオープンされていない場合は 0
		[[nodiscard]]
		int64 size() const noexcept;

		/// @brief ファイルからデータを読み込みます。
		/// @param data 読み込んだデータを格納するバッファ
		/// @param size データのサイズ（バイト）
		/// @return 読み込んだバイト数
		int64 read(void* data, size_t size);

		/// @brief ファイルからデータを読み込みます。
		/// @tparam T 読み込むデータの型
		/// @param data 読み込んだデータを格納する変数
		/// @return 読み込んだバイト数
		template <class T>
			requires std::is_trivially_copyable_v<T>
		int64 read(T& data)
		{
			return read(std::addressof(data), sizeof(T));
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
