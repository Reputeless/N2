#pragma once
#include <cstdint> // std::int8_t, std::int16_t, std::int32_t, std::int64_t, std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t

/// @brief ライブラリのメジャーバージョン
#define SECCAMPLIB_VERSION_MAJOR		1

/// @brief ライブラリのマイナーバージョン
#define SECCAMPLIB_VERSION_MINOR		2

/// @brief ライブラリのリビジョンバージョン
#define SECCAMPLIB_VERSION_REVISION		3

/// @brief ライブラリのバージョン番号
#define SECCAMPLIB_VERSION_NUMBER		((SECCAMPLIB_VERSION_MAJOR * 100 * 100) + (SECCAMPLIB_VERSION_MINOR * 100) + SECCAMPLIB_VERSION_REVISION)

namespace seccamp
{
	using int8  = std::int8_t;
	using int16 = std::int16_t;
	using int32 = std::int32_t;
	using int64 = std::int64_t;

	using uint8  = std::uint8_t;
	using uint16 = std::uint16_t;
	using uint32 = std::uint32_t;
	using uint64 = std::uint64_t;
}

//////////////////////////////////////////////////
//
//	プラットフォーム判定用のマクロ
//
//	SECCAMP_PLATFORM_NAME
//	SECCAMP_PLATFORM(WINDOWS)
//	SECCAMP_PLATFORM(MACOS)
//	SECCAMP_PLATFORM(LINUX)
//	SECCAMP_PLATFORM(IOS)
//	SECCAMP_PLATFORM(ANDROID)
//	SECCAMP_PLATFORM(WEB)
// 
//////////////////////////////////////////////////

#define SECCAMP_PLATFORM(X) SECCAMP_PLATFORM_PRIVATE_DEFINITION_##X()
#define SECCAMP_PLATFORM_PRIVATE_DEFINITION_WINDOWS()	0
#define SECCAMP_PLATFORM_PRIVATE_DEFINITION_MACOS()		0
#define SECCAMP_PLATFORM_PRIVATE_DEFINITION_LINUX()		0
#define SECCAMP_PLATFORM_PRIVATE_DEFINITION_IOS()		0
#define SECCAMP_PLATFORM_PRIVATE_DEFINITION_ANDROID()	0
#define SECCAMP_PLATFORM_PRIVATE_DEFINITION_WEB()		0

#if defined(_WIN32) // Windows

	#define SECCAMP_PLATFORM_NAME	"Windows"
	#undef	SECCAMP_PLATFORM_PRIVATE_DEFINITION_WINDOWS
	#define SECCAMP_PLATFORM_PRIVATE_DEFINITION_WINDOWS()	1

#elif defined(__APPLE__) // macOS, iOS

	#include <TargetConditionals.h> // TARGET_OS_IPHONE, TARGET_IPHONE_SIMULATOR, TARGET_OS_MAC

	#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

		#define SECCAMP_PLATFORM_NAME	"iOS"
		#undef  SECCAMP_PLATFORM_PRIVATE_DEFINITION_IOS
		#define SECCAMP_PLATFORM_PRIVATE_DEFINITION_IOS()	1

	#elif TARGET_OS_MAC
	
		#define SECCAMP_PLATFORM_NAME	"macOS"
		#undef  SECCAMP_PLATFORM_PRIVATE_DEFINITION_MACOS
		#define SECCAMP_PLATFORM_PRIVATE_DEFINITION_MACOS()	1
	
	#else

		#error "Unknown Apple platform"

	#endif

#elif defined(__ANDROID__) // Android

	#define SECCAMP_PLATFORM_NAME	"Android"
	#undef  SECCAMP_PLATFORM_PRIVATE_DEFINITION_ANDROID
	#define SECCAMP_PLATFORM_PRIVATE_DEFINITION_ANDROID()	1

#elif defined(__linux__) // Linux

	#define SECCAMP_PLATFORM_NAME	"Linux"
	#undef  SECCAMP_PLATFORM_PRIVATE_DEFINITION_LINUX
	#define SECCAMP_PLATFORM_PRIVATE_DEFINITION_LINUX()		1

#elif defined(__EMSCRIPTEN__) // Web

	#define SECCAMP_PLATFORM_NAME	"Web"
	#undef  SECCAMP_PLATFORM_PRIVATE_DEFINITION_WEB
	#define SECCAMP_PLATFORM_PRIVATE_DEFINITION_WEB()		1

#else

	#error "Unknown platform"

#endif

//////////////////////////////////////////////////
//
//	コンパイラ判定用のマクロ
//
//	SECCAMP_COMPILER_NAME
//	SECCAMP_BUILD(MSVC)
//	SECCAMP_BUILD(APPLECLANG)
//	SECCAMP_BUILD(CLANG)
//	SECCAMP_BUILD(GCC)
// 
//////////////////////////////////////////////////

#define SECCAMP_COMPILER(X) SECCAMP_COMPILER_PRIVATE_DEFINITION_##X()
#define SECCAMP_COMPILER_PRIVATE_DEFINITION_MSVC()			0
#define SECCAMP_COMPILER_PRIVATE_DEFINITION_APPLE_CLANG()	0
#define SECCAMP_COMPILER_PRIVATE_DEFINITION_CLANG()			0
#define SECCAMP_COMPILER_PRIVATE_DEFINITION_GCC()			0

#if defined(_MSC_VER) // MSVC

	#define SECCAMP_COMPILER_NAME	"Microsoft Visual C++"
	#undef	SECCAMP_COMPILER_PRIVATE_DEFINITION_MSVC
	#define SECCAMP_COMPILER_PRIVATE_DEFINITION_MSVC()	1

#elif (defined(__clang__) && defined(__apple_build_version__)) // Apple Clang

	#define SECCAMP_COMPILER_NAME	"Apple Clang"
	#undef	SECCAMP_COMPILER_PRIVATE_DEFINITION_APPLE_CLANG
	#define SECCAMP_COMPILER_PRIVATE_DEFINITION_APPLE_CLANG()	1

#elif defined(__clang__) // Clang

	#define SECCAMP_COMPILER_NAME	"Clang"
	#undef	SECCAMP_COMPILER_PRIVATE_DEFINITION_CLANG
	#define SECCAMP_COMPILER_PRIVATE_DEFINITION_CLANG()			1

#elif defined(__GNUC__) // GCC

	#define SECCAMP_COMPILER_NAME	"GCC"
	#undef	SECCAMP_COMPILER_PRIVATE_DEFINITION_GCC
	#define SECCAMP_COMPILER_PRIVATE_DEFINITION_GCC()			1

#else

	#error "Unknown compiler"

#endif

//////////////////////////////////////////////////
//
//	ビルドモード判定用のマクロ
//
//	SECCAMP_BUILD_TYPE
//	SECCAMP_BUILD(DEBUG)
//	SECCAMP_BUILD(RELEASE)
// 
//////////////////////////////////////////////////

#define SECCAMP_BUILD(X) SECCAMP_BUILD_PRIVATE_DEFINITION_##X()
#define SECCAMP_BUILD_PRIVATE_DEFINITION_DEBUG()	0
#define SECCAMP_BUILD_PRIVATE_DEFINITION_RELEASE()	0

#if (defined(_DEBUG) || defined(DEBUG)) // Debug ビルド

	#define SECCAMP_BUILD_TYPE	"Debug"
	#undef  SECCAMP_BUILD_PRIVATE_DEFINITION_DEBUG
	#define SECCAMP_BUILD_PRIVATE_DEFINITION_DEBUG()	1

#else // Release ビルド

	#define SECCAMP_BUILD_TYPE	"Release"
	#undef  SECCAMP_BUILD_PRIVATE_DEFINITION_RELEASE
	#define SECCAMP_BUILD_PRIVATE_DEFINITION_RELEASE()	1

#endif
