#include <fstream> // std::ifstream
#include "BinaryFileReader.hpp"
#include "FileSystem.hpp"

namespace seccamp
{
	namespace
	{
		[[nodiscard]]
		static int64 GetFileSize(std::ifstream& file)
		{
			const int64 currentPos = file.tellg();

			file.seekg(0, std::ios::end);

			const int64 size = file.tellg();

			file.seekg(currentPos);

			return size;
		}
	}

	class BinaryFileReader::Impl
	{
	public:

		Impl() = default;

		~Impl()
		{
			close();
		}

		[[nodiscard]]
		bool isOpen() const noexcept
		{
			return m_file.is_open();
		}

		bool open(const std::string_view path)
		{
			if (m_file.is_open())
			{
				close();
			}

			m_file.open(std::string{ path }, std::ios::binary);

			if (m_file.is_open())
			{
				m_fullPath = FileSystem::FullPath(path);
				
				m_size = GetFileSize(m_file);

				return true;
			}
			else
			{
				return false;
			}
		}

		void close()
		{
			m_file.close();

			m_size = 0;

			m_fullPath.clear();
		}

		[[nodiscard]]
		int64 size() const noexcept
		{
			return m_size;
		}

		[[nodiscard]]
		int64 read(void* data, const size_t size)
		{
			m_file.read(static_cast<char*>(data), size);

			return m_file.gcount();
		}

		[[nodiscard]]
		const std::string& fullPath() const noexcept
		{
			return m_fullPath;
		}

	private:

		std::ifstream m_file;

		int64 m_size = 0;

		std::string m_fullPath;
	};

	BinaryFileReader::BinaryFileReader()
		: m_pImpl{ std::make_shared<Impl>() } {}

	BinaryFileReader::BinaryFileReader(const std::string_view path)
		: BinaryFileReader{} // 移譲コンストラクタ
	{
		m_pImpl->open(path);
	}

	bool BinaryFileReader::isOpen() const noexcept
	{
		return m_pImpl->isOpen();
	}

	BinaryFileReader::operator bool() const noexcept
	{
		return m_pImpl->isOpen();
	}

	bool BinaryFileReader::open(const std::string_view path)
	{
		return m_pImpl->open(path);
	}

	void BinaryFileReader::close()
	{
		m_pImpl->close();
	}

	int64 BinaryFileReader::size() const noexcept
	{
		return m_pImpl->size();
	}

	int64 BinaryFileReader::read(void* data, const size_t size)
	{
		return m_pImpl->read(data, size);
	}

	const std::string& BinaryFileReader::fullPath() const noexcept
	{
		return m_pImpl->fullPath();
	}
}
