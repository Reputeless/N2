#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::chrono::milliseconds
#include "Utility.hpp"

namespace seccamp
{
	std::string ToLower(const std::string_view s)
	{
		std::string result{ s };

		for (char& c : result)
		{
			if (InRange(c, 'A', 'Z'))
			{
				c += ('a' - 'A');
			}
		}

		return result;
	}

	std::string ToUpper(const std::string_view s)
	{
		std::string result{ s };

		for (char& c : result)
		{
			if (InRange(c, 'a', 'z'))
			{
				c -= ('a' - 'A');
			}
		}

		return result;
	}

	void Sleep(const int milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds{ milliseconds });
	}
}
