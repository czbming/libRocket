/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef ROCKETCORESTRINGUTILITIES_H
#define ROCKETCORESTRINGUTILITIES_H

#include <Rocket/Core/Header.h>
#include <Rocket/Core/Types.h>
#include <Rocket/Core/String.h>
#include <stdarg.h>

namespace Rocket {
namespace Core {

/**
	Helper functions for string manipulation.
	@author Lloyd Weehuizen
 */

class ROCKETCORE_API StringUtilities
{
public:
	/// Expands character-delimited list of values in a single string to a whitespace-trimmed list
	/// of values.
	/// @param[out] string_list Resulting list of values.
	/// @param[in] string String to expand.
	/// @param[in] delimiter Delimiter found between entries in the string list.
	static void ExpandString(StringList& string_list, const String& string, const char delimiter = ',');
	/// Joins a list of string values into a single string separated by a character delimiter.
	/// @param[out] string Resulting concatenated string.
	/// @param[in] string_list Input list of string values.
	/// @param[in] delimiter Delimiter to insert between the individual values.
	static void JoinString(String& string, const StringList& string_list, const char delimiter = ',');

	/// Hashes a string of data to an integer value using the FNV algorithm.
	/// @param[in] data Data to hash.
	/// @param[in] length Length of the string to hash. If this is -1, the data will be interpreted as a C string.
	/// @return Integer hash of the data.
	static Hash FNVHash(const char* data, int length = -1);

	/// Converts a character array in UTF-8 encoding to a vector of words. The UCS-2 words will be encoded as
	/// either big- or little-endian, depending on the host processor.
	/// @param[in] input Input string in UTF-8 encoding.
	/// @param[out] output Output vector of UCS-2 characters.
	/// @return True if the conversion went successfully, false if any characters had to be skipped (this will occur if they can't fit into UCS-2).
	static bool UTF8toUCS2(const String& input, std::vector< word >& output);
	/// Converts a vector of words in UCS-2 encoding into a character array in UTF-8 encoding. This
	/// function assumes the endianness of the input words to be the same as the host processor.
	/// @param[in] input Input vector in UCS-2 encoding.
	/// @param[out] output Output string in UTF-8 encoding.
	/// @return True if the conversion went successfully, false if not.
	static bool UCS2toUTF8(const std::vector< word >& input, String& output);
	/// Converts an array of words in UCS-2 encoding into a character array in UTF-8 encoding. This
	/// function assumes the endianness of the input words to be the same as the host processor.
	/// @param[in] input Input array of words in UCS-2 encoding.
	/// @param[in] input_size Length of the input array.
	/// @param[out] output Output string in UTF-8 encoding.
	/// @return True if the conversion went successfully, false if not.
	static bool UCS2toUTF8(const word* input, size_t input_size, String& output);

	/// Checks if a given value is a CJK character. This corresponds to Unicode 6.0.
	template < typename CharacterType >
	static bool IsCJKCharacter(CharacterType x)
	{
		if (x >= 0x2E80 && x <= 0x2FA1F)
		{
			// CJK Unified Ideographs
			if (x >= 0x4E00 && x <= 0x9FFF)
				return true;
			// CJK Symbols and Punctuation
			if (x >= 0x3000 && x <= 0x303F)
				return true;
			// CJK Unified Ideographs Extension A
			if (x >= 0x3400 && x <= 0x4DBF)
				return true;
			// CJK Compatibility Ideographs.
			if (x >= 0xF900 && x <= 0xFAFF)
				return true;
			// Halfwidth and Fullwidth Forms
			if (x >= 0xFF00 && x <= 0xFFEF)
				return true;

			// Hiragana
			if (x >= 0x3040 && x <= 0x309F)
				return true;
			// Katakana
			if (x >= 0x30A0 && x <= 0x30FF)
				return true;
			// Bopomofo
			if (x >= 0x3100 && x <= 0x312F)
				return true;
			// Hangul Compatibility Jamo
			if (x >= 0x3130 && x <= 0x318F)
				return true;

			// CJK Radicals Supplement
			if (x >= 0x2E80 && x <= 0x2EFF)
				return true;
			// Kangxi Radicals
			if (x >= 0x2F00 && x <= 0x2FDF)
				return true;
			// Ideographic Description Characters
			if (x >= 0x2FF0 && x <= 0x2FFF)
				return true;
			// CJK Strokes.
			if (x >= 0x31C0 && x <= 0x31EF)
				return true;

			// Kanbun
			if (x >= 0x3190 && x <= 0x319F)
				return true;
			// Bopomofo Extended
			if (x >= 0x31A0 && x <= 0x31BF)
				return true;
			// Katakana Phonetic Extensions
			if (x >= 0x31F0 && x <= 0x31FF)
				return true;
			// Enclosed CJK Letters and Months
			if (x >= 0x3200 && x <= 0x32FF)
				return true;
			// Enclosed CJK Letters and Months
			if (x >= 0x3300 && x <= 0x33FF)
				return true;

			// Hangul Jamo Extended-A
			if (x >= 0xA960 && x <= 0xA97F)
				return true;
			// Hangul Syllables
			if (x >= 0xAC00 && x <= 0xD7AF)
				return true;
			// Hangul Jamo Extended-B
			if (x >= 0xD7B0 && x <= 0xD7FF)
				return true;
			// Kana Supplement
			if (x >= 0x1B000 && x <= 0x1B0FF)
				return true;

			// CJK Unified Ideographs Extension B
			if (x >= 0x20000 && x <= 0x2A6DF)
				return true;
			// CJK Unified Ideographs Extension C
			if (x >= 0x2A700 && x <= 0x2B73F)
				return true;
			// CJK Unified Ideographs Extension D
			if (x >= 0x2B740 && x <= 0x2B81F)
				return true;
			// CJK Compatibility Ideographs Supplement
			if (x >= 0x2F800 && x <= 0x2FA1F)
				return true;

			// Yijing Hexagram Symbols
			if (x >= 0x4DC0 && x <= 0x4DFF)
				return true;
			// Vertical forms
			if (x >= 0xFE10 && x <= 0xFE1F)
				return true;
			// CJK Compatibility Forms
			if (x >= 0xFE30 && x <= 0xFE4F)
				return true;
			// Tai Xuan Hing Symbols
			if (x >= 0x1D300 && x <= 0x1D35F)
				return true;
			// Enclosed Ideographic Supplement 
			if (x >= 0x1F200 && x <= 0x1F2FF)
				return true;
		}

		return false;
	}

	/// Checks if a given value is a whitespace character.
	/// @param[in] x The character to evaluate.
	/// @return True if the character is whitespace, false otherwise.
	template < typename CharacterType >
	static bool IsWhitespace(CharacterType x)
	{
		return (x == '\r' || x == '\n' || x == ' ' || x == '\t');
	}

	/// Strip whitespace characters from the beginning and end of a string.
	/// @param[in] string The string to trim.
	/// @return The stripped string.
	static String StripWhitespace(const String& string);

	/// Operator for STL containers using strings.
	struct ROCKETCORE_API StringComparei
	{
		bool operator()(const String& lhs, const String& rhs) const;
	};
};

}
}

#endif
