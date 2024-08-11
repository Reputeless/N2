#include "TextFileWriter.hpp"
#include "BinaryFileWriter.hpp"

namespace seccamp
{
	class TextFileWriter::Impl
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
			return m_binaryFileWriter.isOpen();
		}

		bool open(const std::string_view path)
		{
			return m_binaryFileWriter.open(path);
		}

		void close()
		{
			m_binaryFileWriter.close();
		}

		void write(const std::string_view s)
		{
			m_binaryFileWriter.write(s.data(), s.size());
		}

		[[nodiscard]]
		const std::string& fullPath() const noexcept
		{
			return m_binaryFileWriter.fullPath();
		}

	private:

		BinaryFileWriter m_binaryFileWriter;
	};

	TextFileWriter::TextFileWriter()
		: m_pImpl{ std::make_shared<Impl>() } {}

	TextFileWriter::TextFileWriter(const std::string_view path)
		: TextFileWriter{} // 移譲コンストラクタ
	{
		m_pImpl->open(path);
	}

	[[nodiscard]]
	bool TextFileWriter::isOpen() const noexcept
	{
		return m_pImpl->isOpen();
	}

	[[nodiscard]]
	bool TextFileWriter::open(const std::string_view path)
	{
		return m_pImpl->open(path);
	}

	TextFileWriter::operator bool() const noexcept
	{
		return m_pImpl->isOpen();
	}

	void TextFileWriter::close()
	{
		m_pImpl->close();
	}

	void TextFileWriter::write(const std::string_view s)
	{
		m_pImpl->write(s);
	}

	void TextFileWriter::writeln(const std::string_view s)
	{
		m_pImpl->write(s);

		m_pImpl->write("\r\n");
	}

	[[nodiscard]]
	const std::string& TextFileWriter::fullPath() const noexcept
	{
		return m_pImpl->fullPath();
	}
}
