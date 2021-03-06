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

#ifndef TEXTURELAYOUTROW_H
#define TEXTURELAYOUTROW_H

#include "TextureLayoutRectangle.h"

namespace Rocket {
namespace Core {

class TextureLayout;

/**
	A texture layout row is a single row of rectangles positioned vertically within a texture.

	@author Peter
 */

class TextureLayoutRow
{
public:
	TextureLayoutRow();
	~TextureLayoutRow();

	/// Attempts to position unplaced rectangles from the layout into this row.
	/// @param[in] layout The layout to position rectangles from.
	/// @param[in] max_width The maximum width of this row.
	/// @param[in] y The y-coordinate of this row.
	/// @return The number of placed rectangles.
	int Generate(TextureLayout& layout, int max_width, int y);

	/// Assigns allocated texture data to all rectangles in this row.
	/// @param[in] texture_data The pointer to the beginning of the texture's data.
	/// @param[in] stride The stride of the texture's surface, in bytes;
	void Allocate(byte* texture_data, int stride);

	/// Returns the width of all placed rectangles.
	inline int GetPlacedWidth() const;
	/// Returns the height of the row.
	/// @return The row's height.
	inline int GetHeight() const;

	/// Resets the placed status for all of the rectangles within this row.
	void Unplace();

private:
	typedef std::vector< TextureLayoutRectangle* > RectangleList;

	int placed_width;
	int height;
	RectangleList rectangles;
};

// Returns the width of all placed rectangles.
inline int TextureLayoutRow::GetPlacedWidth() const
{
	return placed_width;
}

// Returns the height of the row.
inline int TextureLayoutRow::GetHeight() const
{
	return height;
}

}
}

#endif
