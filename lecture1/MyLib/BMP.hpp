#pragma once
#include <string_view> // std::string_view
#include "Common.hpp"

namespace seccamp
{
    class Image; // 前方宣言

    /// @brief 画像を BMP 形式で保存します。
    /// @param image 保存する画像
    /// @param path 保存先のパス
    /// @return 保存に成功した場合 true、それ以外の場合は false
    bool SaveBMP(const Image& image, std::string_view path);

    /// @brief BMP 形式の画像を読み込みます。
    /// @param path 読み込む画像のパス
    /// @return 読み込んだ画像。読み込みに失敗した場合は空の画像
    [[nodiscard]]
    Image LoadBMP(std::string_view path);
}
