#include "TextFileReader.hpp"
#include "BinaryFileReader.hpp"

namespace seccamp
{
	class TextFileReader::Impl
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
			return m_binaryFileReader.isOpen();
		}

		bool open(const std::string_view path)
		{
			return m_binaryFileReader.open(path);
		}

		void close()
		{
			m_binaryFileReader.close();
		}

		bool readLine(std::string& line)
		{
			line.clear();

			int32 readBytes = 0;

			for (;;)
			{
				char c = '\0';

				if (m_binaryFileReader.read(&c, 1) == 0)
				{
					if (readBytes == 0)
					{
						return false;
					}
					else
					{
						break;
					}
				}

				++readBytes;

				if (c == '\r')
				{
					continue;
				}
				else if (c == '\n')
				{
					break;
				}

				line.push_back(c);
			}

			return true;
		}

		const std::string& fullPath() const noexcept
		{
			return m_binaryFileReader.fullPath();
		}

	private:

		BinaryFileReader m_binaryFileReader;
	};

	TextFileReader::TextFileReader()
		: m_pImpl{ std::make_shared<Impl>() } {}

	TextFileReader::TextFileReader(const std::string_view path)
		: TextFileReader{} // 移譲コンストラクタ
	{
		m_pImpl->open(path);
	}

	bool TextFileReader::isOpen() const noexcept
	{
		return m_pImpl->isOpen();
	}

	TextFileReader::operator bool() const noexcept
	{
		return m_pImpl->isOpen();
	}

	bool TextFileReader::open(const std::string_view path)
	{
		return m_pImpl->open(path);
	}

	void TextFileReader::close()
	{
		m_pImpl->close();
	}

	bool TextFileReader::readLine(std::string& line)
	{
		return m_pImpl->readLine(line);
	}

	const std::string& TextFileReader::fullPath() const noexcept
	{
		return m_pImpl->fullPath();
	}
}
