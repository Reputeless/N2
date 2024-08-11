#pragma once
#include <iostream> // std::ostream, std::istream
#include <concepts> // std::integral
#include <format> // std::formatter
#include "Common.hpp"

namespace seccamp
{
    /// @brief 色（RGBA）
    struct Color
    {
        /// @brief 赤成分
        uint8 r;

        /// @brief 緑成分
        uint8 g;

        /// @brief 青成分
        uint8 b;

        /// @brief アルファ成分
        uint8 a;

        /// @brief デフォルトコンストラクタ
        [[nodiscard]]
        Color() = default;

        /// @brief 色を作成します。
        /// @param rgb RGB 成分 [0, 255]
        [[nodiscard]]
        explicit constexpr Color(uint8 rgb) noexcept
            : r{ rgb }
			, g{ rgb }
			, b{ rgb }
			, a{ 255 } {}

        /// @brief 色を作成します。
        /// @param rgb RGB 成分 [0, 255]
        [[nodiscard]]
        explicit constexpr Color(std::integral auto rgb) noexcept
            : r{ static_cast<uint8>(rgb) }
            , g{ static_cast<uint8>(rgb) }
            , b{ static_cast<uint8>(rgb) }
            , a{ 255 } {}

        /// @brief 色を作成します。
        /// @param rgb RGB 成分 [0, 255]
        /// @param _a アルファ成分 [0, 255]
        [[nodiscard]]
        constexpr Color(uint8 rgb, uint8 _a) noexcept
            : r{ rgb }
            , g{ rgb }
            , b{ rgb }
            , a{ _a } {}

        /// @brief 色を作成します。
        /// @param rgb RGB 成分 [0, 255]
        /// @param _a アルファ成分 [0, 255]
		[[nodiscard]]
        constexpr Color(std::integral auto rgb, std::integral auto _a) noexcept
            : r{ static_cast<uint8>(rgb) }
			, g{ static_cast<uint8>(rgb) }
			, b{ static_cast<uint8>(rgb) }
			, a{ static_cast<uint8>(_a) } {}

        /// @brief 色を作成します。
        /// @param _r R 成分 [0, 255]
        /// @param _g G 成分 [0, 255]
        /// @param _b B 成分 [0, 255]
        [[nodiscard]]
        constexpr Color(uint8 _r, uint8 _g, uint8 _b) noexcept
			: r{ _r }
			, g{ _g }
			, b{ _b }
			, a{ 255 } {}

        /// @brief 色を作成します。
        /// @param _r R 成分 [0, 255]
        /// @param _g G 成分 [0, 255]
        /// @param _b B 成分 [0, 255]
		[[nodiscard]]
        constexpr Color(std::integral auto _r, std::integral auto _g, std::integral auto _b) noexcept
            : r{ static_cast<uint8>(_r) }
            , g{ static_cast<uint8>(_g) }
            , b{ static_cast<uint8>(_b) }
            , a{ 255 } {}

        /// @brief 色を作成します。
        /// @param _r R 成分 [0, 255]
        /// @param _g G 成分 [0, 255]
        /// @param _b B 成分 [0, 255]
        /// @param _a アルファ成分 [0, 255]
        [[nodiscard]]
        constexpr Color(uint8 _r, uint8 _g, uint8 _b, uint8 _a) noexcept
			: r{ _r }
			, g{ _g }
			, b{ _b }
			, a{ _a } {}

        /// @brief 色を作成します。
        /// @param _r R 成分 [0, 255]
        /// @param _g G 成分 [0, 255]
        /// @param _b B 成分 [0, 255]
        /// @param _a アルファ成分 [0, 255]
		[[nodiscard]]
        constexpr Color(std::integral auto _r, std::integral auto _g, std::integral auto _b, std::integral auto _a) noexcept
			: r{ static_cast<uint8>(_r) }
			, g{ static_cast<uint8>(_g) }
			, b{ static_cast<uint8>(_b) }
			, a{ static_cast<uint8>(_a) } {}

        [[nodiscard]]
        friend constexpr bool operator ==(const Color& lhs, const Color& rhs) noexcept = default;

        /// @brief グレースケール値を返します。
        /// @return グレースケール値
        [[nodiscard]]
        constexpr uint8 grayscaleUint8() const noexcept
        {
            return static_cast<uint8>((0.299 * r) + (0.587 * g) + (0.114 * b));
        }

        /// @brief グレースケール値を返します。
        /// @return グレースケール値
		[[nodiscard]]
        constexpr double grayscale() const noexcept
		{
            return ((0.299 / 255.0 * r) + (0.587 / 255.0 * g) + (0.114 / 255.0 * b));
		}

        /// @brief 出力ストリームに書き込みます。
        /// @param os 出力ストリーム
        /// @param c 書き込む値
        /// @return 出力ストリーム
        friend std::ostream& operator <<(std::ostream& os, const Color& c)
		{
			return os << '(' << static_cast<uint16>(c.r) << ", "
                << static_cast<uint16>(c.g) << ", "
                << static_cast<uint16>(c.b) << ", "
                << static_cast<uint16>(c.a) << ')';
		}

        /// @brief 入力ストリームから読み込みます。
        /// @param is 入力ストリーム
        /// @param c 読み込んだ値の格納先
        /// @return 入力ストリーム
        friend std::istream& operator >>(std::istream& is, Color& c)
        {
            char t;
            uint16 r, g, b, a;
            is >> t >> r >> t >> g >> t >> b >> t;
            
            if (t == ')')
			{
				c.r = static_cast<uint8>(r);
				c.g = static_cast<uint8>(g);
				c.b = static_cast<uint8>(b);
				c.a = 255;
				return is;
			}
            else
            {
                is >> a >> t;
                c.r = static_cast<uint8>(r);
                c.g = static_cast<uint8>(g);
                c.b = static_cast<uint8>(b);
                c.a = static_cast<uint8>(a);
                return is;
            }
		}
    };

    namespace Palette
    {
        /// @brief 黒色
        inline constexpr Color Black{ 0, 0, 0 };

        /// @brief 白色
        inline constexpr Color White{ 255, 255, 255 };
    }
}

/// @brief Color 型を std::format に対応させるための std::formatter 特殊化
template<>
struct std::formatter<seccamp::Color>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    auto format(const seccamp::Color& p, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "({}, {}, {}, {})", p.r, p.g, p.b, p.a);
    }
};
