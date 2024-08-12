#include "BMP.hpp"
#include "Image.hpp"
#include "BinaryFileWriter.hpp"
#include "BinaryFileReader.hpp"

namespace seccamp
{
// クラスを 2 バイト境界にパックする
#pragma pack(push, 2)

	/// @brief Windows Bitmap ファイルのヘッダ
	/// @see https://www.setsuki.com/hsp/ext/bmp.htm
	struct BMPHeader
	{
		uint16 bfType;
		uint32 bfSize;
		uint16 bfReserved1;
		uint16 bfReserved2;
		uint32 bfOffBits;
		uint32 biSize;
		int32  biWidth;
		int32  biHeight;
		uint16 biPlanes;
		uint16 biBitCount;
		uint32 biCompression;
		uint32 biSizeImage;
		int32  biXPelsPerMeter;
		int32  biYPelsPerMeter;
		uint32 biClrUsed;
		uint32 biClrImportant;

		/// @brief BMP ヘッダを作成します。
		/// @param width 画像の幅（ピクセル）
		/// @param height 画像の高さ（ピクセル）
		/// @param size_bytes 画像データのサイズ（バイト）
		/// @return BMP ヘッダ
		[[nodiscard]]
		static constexpr BMPHeader Make(int32 width, int32 height, uint32 size_bytes) noexcept
		{
			return
			{
				.bfType				= 0x4d42,
				.bfSize				= static_cast<uint32>(sizeof(BMPHeader) + size_bytes),
				.bfReserved1		= 0,
				.bfReserved2		= 0,
				.bfOffBits			= sizeof(BMPHeader),
				.biSize				= 40,
				.biWidth			= width,
				.biHeight			= height,
				.biPlanes			= 1,
				.biBitCount			= 24,
				.biCompression		= 0,
				.biSizeImage		= size_bytes,
				.biXPelsPerMeter	= 0,
				.biYPelsPerMeter	= 0,
				.biClrUsed			= 0,
				.biClrImportant		= 0
			};
		}
	};

	// ヘッダのサイズが 54 バイトであることを確認
	static_assert(sizeof(BMPHeader) == 54);

// パッキングをデフォルトに戻す
#pragma pack(pop)

    bool SaveBMP(const Image& image, const std::string_view path)
    {
		if (image.isEmpty())
		{
			return false;
		}

		const int32 width			= image.width();
		const int32 height			= image.height();
		const uint32 strideBytes	= (width * 3 + width % 4); // BMP の 1 行は 4 の倍数バイトにアラインメントされる
		const uint32 sizeBytes		= (strideBytes * height);
		
		BinaryFileWriter writer{ path };

		if (not writer.isOpen())
		{
			return false;
		}

		// BMP ファイルヘッダの書き込み
		{
			const BMPHeader header = BMPHeader::Make(width, height, sizeBytes);
			writer.write(header);
		}

		// 各行の書き込み
		{
			// 1 行分のデータを格納するバッファ
			std::vector<uint8> line(strideBytes);

			// 現在見ている image の行の先頭ポインタ
			const Color* pSrcLine = image[height - 1]; // BMP は下から上に書き込む

			for (int32 y = 0; y < height; ++y)
			{
				// バッファの先頭ポインタ
				uint8* pDst = line.data();

				// 現在見ているピクセルのポインタ
				const Color* pSrc = pSrcLine;

				for (int32 x = 0; x < width; ++x)
				{
					*pDst++ = pSrc->b;
					*pDst++ = pSrc->g;
					*pDst++ = pSrc->r;

					// 次のピクセルへ
					++pSrc;
				}

				// 1 行分のデータを書き込む
				writer.write(line.data(), strideBytes);

				// image を見ているポインタを 1 行上に移動
				pSrcLine -= width;
			}
		}

		return true;
    }

    Image LoadBMP(const std::string_view path)
    {
		BinaryFileReader reader{ path };

		if (not reader.isOpen())
		{
			return{};
		}

		// BMP ファイルヘッダの読み込み
		BMPHeader header;
		if (reader.read(&header, sizeof(BMPHeader)) != sizeof(BMPHeader))
		{
			return{};
		}

		// 下から上方向に格納？
		const bool reverse	= (header.biHeight > 0); // BMP は下から上に書き込まれる。biHeight が負の場合は上から下に書き込まれている
		
		// 画像の幅（ピクセル）
		const int32 width	= header.biWidth;
		
		// 画像の高さ（ピクセル）
		const int32 height	= (reverse ? header.biHeight : -header.biHeight);

		// 1 ピクセルあたりのビット数
		const int32 depth = header.biBitCount;

		// とりあえず 24 ビットのみ対応
		if (depth != 24)
		{
			return{};
		}

		// 1 行分のデータのサイズ（バイト）
		const size_t strideBytes = (width * 3 + width % 4);

		// 次の行へのオフセット
		const int32 lineStep = (reverse ? -width : width);

		Image image{ width, height };

		// 書き込み先の行の先頭ポインタ
		Color* pDstLine = image[reverse ? height - 1 : 0];

		std::vector<uint8> line(strideBytes);

		for (int32 y = 0; y < height; ++y)
		{
			// 1 行分のデータを読み込む
			if (reader.read(line.data(), strideBytes) != strideBytes)
			{
				return{};
			}

			Color* pDst = pDstLine;
			const uint8* pSrc = line.data();

			for (int32 x = 0; x < width; ++x)
			{
				pDst->b = *pSrc++;
				pDst->g = *pSrc++;
				pDst->r = *pSrc++;

				++pDst;
			}

			// 書き込み先の行を次の行へ移動
			pDstLine += lineStep;
		}

        return image;
    }
}
