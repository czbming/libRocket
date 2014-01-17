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

#include "precompiled.h"
#include "TextureLayoutRow.h"
#include "TextureLayout.h"

namespace Rocket {
namespace Core {

TextureLayoutRow::TextureLayoutRow()
{
	placed_width = 1;
	height = 0;
}

TextureLayoutRow::~TextureLayoutRow()
{
}

// Attempts to position unplaced rectangles from the layout into this row.
int TextureLayoutRow::Generate(TextureLayout& layout, int max_width, int y)
{
	int placed_rectangles = 0;

	while(!layout.unplaced_rectangles.empty())
	{
		TextureLayoutRectangle* rectangle = layout.unplaced_rectangles.front();
		if (placed_width + rectangle->GetDimensions().x + 1 > max_width)
			break;

		// Increment the row height if necessary.
		height = Math::Max(height, rectangle->GetDimensions().y);

		// Add this glyph onto our list and mark it as placed.
		rectangles.push_back(rectangle);
		if (layout.has_generated)
			rectangle->Place(layout.GetNumTextures()-1, Vector2i(placed_width, y));
		else
			rectangle->Place(layout.GetNumTextures(), Vector2i(placed_width, y));
		++placed_rectangles;

		// Increment our width. An extra pixel is added on so the rectangles aren't pushed up
		// against each other. This will avoid filtering artifacts.
		if (rectangle->GetDimensions().x > 0)
			placed_width += rectangle->GetDimensions().x + 1;

		layout.rectangles.push_back(rectangle);
		layout.unplaced_rectangles.pop();
	}

	return placed_rectangles;
}

// Assigns allocated texture data to all rectangles in this row.
void TextureLayoutRow::Allocate(byte* texture_data, int stride)
{
	size_t rectangle_count = rectangles.size();
	for (size_t i = 0; i < rectangle_count; ++i)
		rectangles[i]->Allocate(texture_data, stride);
}

// Resets the placed status for all of the rectangles within this row.
void TextureLayoutRow::Unplace()
{
	size_t rectangle_count = rectangles.size();
	for (size_t i = 0; i < rectangle_count; ++i)
		rectangles[i]->Unplace();
}

}
}
