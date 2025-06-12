![OAPV](/readme/img/oapv_logo_black_bar_256.png#gh-light-mode-only) ![OAPV](/readme/img/oapv_logo_white_bar_256.png#gh-dark-mode-only)
# OpenAPV (Open Advanced Professional Video Codec)

[![Build and test](https://github.com/AcademySoftwareFoundation/openapv/actions/workflows/build.yml/badge.svg)](https://github.com/AcademySoftwareFoundation/openapv/actions/workflows/build.yml)

OpenAPV provides the reference implementation of the [APV codec](#apv-codec) which can be used to record professional-grade video and associated metadata without quality degradation. OpenAPV is free and open source software provided by [LICENSE](#license).

The OpenAPV supports the following features:

- fully compliant with 422-10 and 400-10 profile of [APV codec](#apv-codec)
- Low complexity by optimization for ARM NEON and x86(64bit) SEE/AVX CPU
- Supports tile-based multi-threading
- Supports Various metadata including HDR10/10+ and user-defined format
- Constant QP (CQP), average bitrate (ABR), and constant rate factor (CRF) are supported


## APV codec
The APV codec is a professional video codec, which was developed in response to the need for professional level high quality video recording and post production. The primary purpose of the APV codec is for use in professional video recording and editing workflows for various types of content.

APV codec utilizes technologies known to be over 20 years to achieve a royalty free codec. APV builds a video codec using only conventional coding technologies, which consist of traditional methods published between the early 1980s and the end of the 1990s.

The APV codec standard has the following features:

- Perceptually lossless video quality, which is close to raw video quality
- Low complexity and high throughput intra frame only coding without pixel domain prediction
- Support for high bit-rate range up to a few Gbps for 2K, 4K and 8K resolution content, enabled by a lightweight entropy coding scheme
- Frame tiling for immersive content and for enabling parallel encoding and decoding
- Support for various chroma sampling formats from 4:2:2 to 4:4:4, and bit-depths from 10 to 16
- Support for multiple decoding and re-encoding without severe visual quality degradation
- Support multi-view video and auxiliary video like depth, alpha, and preview
- Support various metadata including HDR10/10+ and user-definded format

### Related specification
- APV Codec (bitstream): [https://datatracker.ietf.org/doc/draft-lim-apv/](https://datatracker.ietf.org/doc/draft-lim-apv/)
  - Scope of OpenAPV project
- APV ISO based media file format: [APV-ISOBMFF](/readme/apv_isobmff.md)
- APV RTP payload format: [https://datatracker.ietf.org/doc/draft-lim-rtp-apv/](https://datatracker.ietf.org/doc/draft-lim-rtp-apv/)

## How to build
- Build Requirements
  - CMake (download from [https://cmake.org/](https://cmake.org/))
  - GCC

  For ARM
  - gcc-aarch64-linux-gnu
  - binutils-aarch64-linux-gnu

  For Windows (crosscompile)
  - mingw-w64
  - mingw-w64-tools

- Build Instructions PC (Linux)
  ```
  cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
  cmake --build build
  ```

- Build Instructions ARM (Crosscompile)
  ```
  cmake -S . -B build-arm -DCMAKE_TOOLCHAIN_FILE=aarch64_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
  cmake --build build-arm
  ```

- Build Instructions Windows (Crosscompile)
  ```
  cmake -S . -B build-windows -DCMAKE_TOOLCHAIN_FILE=windows_x86_64_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
  cmake --build build-windows
  ```

- Output Location
  - Executable applications can be found under build*/bin/
  - Library files can be found under build*/lib/

## How to use applications
### Encoder

Encoder as input require raw YCbCr file (422, 444), 10-bit or more.

Displaying help:

    oapv_app_enc --help

Encoding:

    oapv_app_enc -i input_1920x1080_yuv422_10bit.yuv -w 1920 -h 1080 -d 10 -z 30 --input-csp 2 -o encoded.apv
    oapv_app_enc -i input.y4m -o encoded.apv

### Decoder

Decoder output can be in yuv or y4m formats.

Displaying help:

    oapv_app_dec --help

Decoding:

    oapv_app_dec -i encoded.apv -o output.y4m

## Utility

### Graphical APV bitstream parser

Pattern file of APV bitstream for [ImHex](https://github.com/WerWolv/ImHex) is provided [here](/util/apv.hexpat).
1. Install [ImHex](https://github.com/WerWolv/ImHex) application
2. Download [APV pattern file](/util/apv.hexpat)
2. Open APV bitstream (\*.apv file) with ImHex
3. Import the APV pattern file on Pattern editor view of ImHex and apply

![APV_on_ImHex](/readme/img/apv_parser_on_imhex.png)

## Testing

In build directory run ``ctest``

## Packaging

For generating package ready for distribution (default deb) execute in build directory ``cpack``,  or other formats (tgz, zip etc.) ``cpack -G TGZ``.

## Versioning

This project is using folowing versioning scheme ``API-SET.MAJOR.MINOR.PATCH``. It's mostly based on Semantic Versioning with addition of API-SET on first place.
Project and library is following one common version number.

## License

See [LICENSE](LICENSE) file for details.

## Graphic logo
### logo for light mode
![OAPV](/readme/img/oapv_logo_black_bar_64.png) ![OAPV](/readme/img/oapv_logo_black_bar_128.png) ![OAPV](/readme/img/oapv_logo_black_bar_256.png)

### logo for dark mode
![OAPV](/readme/img/oapv_logo_white_bar_64.png) ![OAPV](/readme/img/oapv_logo_white_bar_128.png) ![OAPV](/readme/img/oapv_logo_white_bar_256.png)
