#include <filesystem> // std::filesystem::path, std::filesystem::absolute
#include "FileSystem.hpp"

namespace seccamp
{
	namespace FileSystem
	{
		std::string FullPath(const std::string_view path)
		{
			return std::filesystem::absolute(path).string();
		}

		std::string Extension(const std::string_view path)
		{
			return std::filesystem::path{ path }.extension().string();
		}
	}
}
