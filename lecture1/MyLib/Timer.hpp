#pragma once
#include <print> // std::println
#include <chrono> // std::chrono::high_resolution_clock, std::chrono::time_point, std::chrono::duration_cast, std::chrono::microseconds
#include "Common.hpp"

namespace seccamp
{
	class Timer
	{
	public:

		void print() const
		{
			const auto end = std::chrono::high_resolution_clock::now();
			const auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - m_start).count();
			std::println("Time: {} us ({} ms)", us, (us / 1000));
		}

	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> m_start = std::chrono::high_resolution_clock::now();
	};
}
