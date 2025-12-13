// utf_reader.h  (single-file module)
// - read_file_to_utf8(path, out, detected_encoding)
// - returns true on success, out contains UTF-8 text.
//
// Compile: g++/clang++/msvc should work (codecvt is deprecated but available).

#ifndef UTF_READER_H
#define UTF_READER_H

#include <codecvt> // deprecated in C++17 but available on major compilers
#include <cstdint>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <vector>


// Read file at 'path' and convert to UTF-8 in 'out'.
// If provided, set detected_encoding to a short name like "UTF-8", "UTF-16LE", etc.
inline bool read_file_to_utf8(
    const std::string& path,
    std::string&       out,
    std::string*       detected_encoding = nullptr,
    std::string*       err               = nullptr)
{
    out.clear();
    if(detected_encoding) *detected_encoding = "unknown";
    if(err) *err = "";

    // Read whole file as bytes
    std::ifstream ifs(path, std::ios::binary);
    if(!ifs)
    {
        if(err) *err = "cannot open file";
        return false;
    }

    std::vector<uint8_t> buf((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());

    size_t n = buf.size();
    if(n == 0)
    {
        out.clear();
        if(detected_encoding) *detected_encoding = "empty";
        return true;
    }

    auto startsWith = [&](const std::vector<uint8_t>& b, const std::initializer_list<uint8_t>& p) -> bool
    {
        size_t plen = std::distance(p.begin(), p.end());
        if(b.size() < plen) return false;
        size_t i = 0;
        for(uint8_t x : p)
        {
            if(b[i++] != x) return false;
        }
        return true;
    };

    // Detect BOM
    bool   is_utf8    = false;
    bool   is_utf16le = false;
    bool   is_utf16be = false;
    bool   is_utf32le = false;
    bool   is_utf32be = false;
    size_t offset     = 0;

    if(startsWith(buf, { 0xEF, 0xBB, 0xBF }))
    {
        is_utf8 = true;
        offset  = 3;
        if(detected_encoding) *detected_encoding = "UTF-8 (BOM)";
    }
    else if(startsWith(buf, { 0xFF, 0xFE, 0x00, 0x00 }))
    {
        is_utf32le = true;
        offset     = 4;
        if(detected_encoding) *detected_encoding = "UTF-32LE (BOM)";
    }
    else if(startsWith(buf, { 0x00, 0x00, 0xFE, 0xFF }))
    {
        is_utf32be = true;
        offset     = 4;
        if(detected_encoding) *detected_encoding = "UTF-32BE (BOM)";
    }
    else if(startsWith(buf, { 0xFF, 0xFE }))
    {
        is_utf16le = true;
        offset     = 2;
        if(detected_encoding) *detected_encoding = "UTF-16LE (BOM)";
    }
    else if(startsWith(buf, { 0xFE, 0xFF }))
    {
        is_utf16be = true;
        offset     = 2;
        if(detected_encoding) *detected_encoding = "UTF-16BE (BOM)";
    }
    else
    {
        // No BOM: assume UTF-8 by default (common). If you expect UTF-16 files without BOM, you may add heuristics.
        is_utf8 = true;
        offset  = 0;
        if(detected_encoding) *detected_encoding = "UTF-8 (no BOM)";
    }

    try
    {
        if(is_utf8)
        {
            // UTF-8: just copy remaining bytes
            out.assign(reinterpret_cast<const char*>(buf.data() + offset), buf.size() - offset);
            return true;
        }
        else if(is_utf16le || is_utf16be)
        {
            // Build char16_t buffer
            if((buf.size() - offset) % 2 != 0)
            {
                if(err) *err = "odd number of bytes for UTF-16 data";
                return false;
            }
            std::u16string u16;
            u16.resize((buf.size() - offset) / 2);
            for(size_t i = 0; i < u16.size(); ++i)
            {
                uint8_t  b1  = buf[offset + 2 * i];
                uint8_t  b2  = buf[offset + 2 * i + 1];
                uint16_t val = 0;
                if(is_utf16le)
                {
                    val = static_cast<uint16_t>(b1) | (static_cast<uint16_t>(b2) << 8);
                }
                else
                {
                    // BE
                    val = (static_cast<uint16_t>(b1) << 8) | static_cast<uint16_t>(b2);
                }
                u16[i] = static_cast<char16_t>(val);
            }
            // convert UTF-16 to UTF-8
            std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
            out = conv.to_bytes(u16);
            return true;
        }
        else if(is_utf32le || is_utf32be)
        {
            // Build char32_t buffer
            if((buf.size() - offset) % 4 != 0)
            {
                if(err) *err = "byte count not multiple of 4 for UTF-32 data";
                return false;
            }
            std::u32string u32;
            u32.resize((buf.size() - offset) / 4);
            for(size_t i = 0; i < u32.size(); ++i)
            {
                uint8_t  b1  = buf[offset + 4 * i + 0];
                uint8_t  b2  = buf[offset + 4 * i + 1];
                uint8_t  b3  = buf[offset + 4 * i + 2];
                uint8_t  b4  = buf[offset + 4 * i + 3];
                uint32_t val = 0;
                if(is_utf32le)
                {
                    val = (uint32_t)b1 | ((uint32_t)b2 << 8) | ((uint32_t)b3 << 16) | ((uint32_t)b4 << 24);
                }
                else
                {
                    val = ((uint32_t)b1 << 24) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 8) | (uint32_t)b4;
                }
                u32[i] = static_cast<char32_t>(val);
            }
            // convert UTF-32 to UTF-8
            std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv32;
            out = conv32.to_bytes(u32);
            return true;
        }
    }
    catch(const std::range_error& e)
    {
        if(err) *err = std::string("conversion range_error: ") + e.what();
        return false;
    }
    catch(const std::exception& e)
    {
        if(err) *err = std::string("exception: ") + e.what();
        return false;
    }

    if(err) *err = "unknown encoding handling path";
    return false;
}

#endif // UTF_READER_H
