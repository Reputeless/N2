#include <print>
#include "MyLib/Common.hpp"
#include "MyLib/Utility.hpp"
#include "MyLib/Point.hpp"
#include "MyLib/FileSystem.hpp"
#include "MyLib/Timer.hpp"
#include "MyLib/BinaryFileWriter.hpp"
#include "MyLib/BinaryFileReader.hpp"
#include "MyLib/TextFileWriter.hpp"
#include "MyLib/TextFileReader.hpp"
#include "MyLib/Color.hpp"
#include "MyLib/Image.hpp"
#include "MyLib/BMP.hpp"

using namespace seccamp;

int main()
{
	std::println("---- Common.hpp ----");
	{
		std::println("Hello, seccamp!");
		std::println("SECCAMPLIB_VERSION_MAJOR:  {}", SECCAMPLIB_VERSION_MAJOR);
		std::println("SECCAMPLIB_VERSION_MINOR:  {}", SECCAMPLIB_VERSION_MINOR);
		std::println("SECCAMPLIB_VERSION_REVISION:  {}", SECCAMPLIB_VERSION_REVISION);
		std::println("SECCAMPLIB_VERSION_NUMBER:  {}", SECCAMPLIB_VERSION_NUMBER);

		std::println("sizeof(int8): {}", sizeof(int8));
		std::println("sizeof(int16): {}", sizeof(int16));
		std::println("sizeof(int32): {}", sizeof(int32));
		std::println("sizeof(int64): {}", sizeof(int64));

		std::println("sizeof(uint8): {}", sizeof(uint8));
		std::println("sizeof(uint16): {}", sizeof(uint16));
		std::println("sizeof(uint32): {}", sizeof(uint32));
		std::println("sizeof(uint64): {}", sizeof(uint64));

		std::println("SECCAMP_PLATFORM_NAME: {}", SECCAMP_PLATFORM_NAME);
		std::println("SECCAMP_COMPILER_NAME: {}", SECCAMP_COMPILER_NAME);
		std::println("SECCAMP_BUILD_TYPE: {}", SECCAMP_BUILD_TYPE);

		#if SECCAMP_PLATFORM(WINDOWS)
			std::println("Windows");
		#elif SECCAMP_PLATFORM(MACOS)
			std::println("macOS");
		#elif SECCAMP_PLATFORM(LINUX)
			std::println("Linux");
		#else
			std::println("Other");
		#endif

		#if SECCAMP_COMPILER(MSVC)
			std::println("MSVC");
		#elif SECCAMP_COMPILER(GCC)
			std::println("GCC");
		#elif SECCAMP_COMPILER(APPLE_CLANG)
			std::println("Apple Clang");
		#else
			std::println("Other");
		#endif

		#if SECCAMP_BUILD(DEBUG)
			std::println("Debug");
		#else
			std::println("Release");
		#endif
	}

	std::println("---- Utility.hpp ----");
	{
		std::println("IsEven(20): {}", IsEven(20));
		std::println("IsEven(21): {}", IsEven(21));
		std::println("IsOdd(20): {}", IsOdd(20));
		std::println("IsOdd(21): {}", IsOdd(21));
		std::println("ToLower(\"Hello, seccamp!\"): {}", ToLower("Hello, seccamp!"));
		std::println("ToUpper(\"Hello, seccamp!\"): {}", ToUpper("Hello, seccamp!"));
	}

	std::println("---- Point.hpp ----");
	{
		std::println("{}", Point{ 100, 200 } + Point{ 1, 2 });
		std::println("{}", 2 * Point{ 100, 200 });
		std::println("{}", Point{ 1, 2 } == Point{ 1, 2 });
	}

	std::println("---- FileSystem.hpp ----");
	{
		std::println("FileSystem::FullPath(\"test.txt\"): {}", FileSystem::FullPath("test.txt"));
		std::println("FileSystem::Extension(\"test.txt\"): {}", FileSystem::Extension("test.txt"));
		std::println("FileSystem::Extension(\"test\"): {}", FileSystem::Extension("test"));
	}

	std::println("---- Timer.hpp ----");
	{
		Timer timer;
		Sleep(200);
		timer.print();
	}

	std::println("---- BinaryFileWriter.hpp ----");
	{
		BinaryFileWriter writer{ "test.bin" };
		std::println("writer.isOpen(): {}", writer.isOpen());
		std::println("writer.fullPath(): {}", writer.fullPath());

		const std::string str = "Hello, seccamp!";
		const uint64 length = str.size();
		writer.write(length);
		writer.write(str.data(), str.size());

		const int32 a = 123;
		const double b = 1.25;
		const Point p{ 100, 200 };
		writer.write(a);
		writer.write(b);
		writer.write(p);
	}

	std::println("---- BinaryFileReader.hpp ----");
	{
		BinaryFileReader reader{ "test.bin" };
		std::println("reader.isOpen(): {}", reader.isOpen());
		std::println("reader.fullPath(): {}", reader.fullPath());
		std::println("reader.size(): {}", reader.size());

		uint64 length;
		reader.read(length);
		std::println("length: {}", length);

		std::string str;
		str.resize(length);
		reader.read(str.data(), str.size());
		std::println("str: {}", str);

		int32 a;
		double b;
		Point p;
		reader.read(a);
		reader.read(b);
		reader.read(p);
		std::println("a: {}", a);
		std::println("b: {}", b);
		std::println("p: {}", p);
	}

	std::println("---- TextFileWriter.hpp ----");
	{
		TextFileWriter writer{ "test.txt" };
		std::println("writer.isOpen(): {}", writer.isOpen());
		std::println("writer.fullPath(): {}", writer.fullPath());

		writer.writeln("Hello, seccamp!");
		writer.writeln("こんにちは！");
		writer.writeln("");
		writer.writeln("{}/{}/{}", 2024, 8, 13);
	}

	std::println("---- TextFileReader.hpp ----");
	{
		TextFileReader reader{ "test.txt" };
		std::println("reader.isOpen(): {}", reader.isOpen());
		std::println("reader.fullPath(): {}", reader.fullPath());

		std::string line;
		while (reader.readLine(line))
		{
			std::println("{}", line);
		}
	}

	std::println("---- Color.hpp ----");
	{
		std::println("{}", Color{ 255 });
		std::println("{}", Color{ 0, 255, 0 });
		std::println("{}", Color{ 0, 0, 255, 128 });

		std::println("{}", Color{ 11, 22, 33 }.grayscaleUint8());
		std::println("{}", Color{ 11, 22, 33 }.grayscale());

		std::println("{}", Palette::Black);
		std::println("{}", Palette::White);
	}

	std::println("---- Image.hpp & BMP.hpp ----");
	{
		{
			Image image(Size{ 400, 300 }, Color{ 220, 240, 255 });

			for (int32 y = 40; y < 60; ++y)
			{
				for (int32 x = 0; x < image.width(); ++x)
				{
					image[y][x] = Palette::Black;
				}
			}

			image.save("image.bmp");
		}

		{
			Image image{ "image.bmp" };

			for (int32 y = 0; y < image.height(); ++y)
			{
				for (int32 x = 40; x < 60; ++x)
				{
					image[y][x] = Palette::White;
				}
			}

			image.save("image2.bmp");
		}

		{
			Image image{ "seccamp.bmp" };

			for (auto& pixel : image)
			{
				pixel = Color{ pixel.grayscaleUint8() };
			}

			image.save("seccamp_gray.bmp");
		}
	}
}
