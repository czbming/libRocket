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
#include "TextureResource.h"
#include "FontFaceHandle.h"
#include "TextureDatabase.h"
#include "TextureLayoutTexture.h"
#include <Rocket/Core.h>

namespace Rocket {
namespace Core {

TextureResource::TextureResource()
{
	texture_dirty = false;
}

TextureResource::~TextureResource()
{
	TextureDatabase::RemoveTexture(this);
}

// Attempts to load a texture from the application into the resource.
bool TextureResource::Load(const String& _source)
{
	Release();
	source = _source;

	return true;
}

// Dirty the texture.
void TextureResource::Update()
{
	texture_dirty = true;
}

// Returns the resource's underlying texture.
TextureHandle TextureResource::GetHandle(RenderInterface* render_interface) const
{
	TextureDataMap::iterator texture_iterator = texture_data.find(render_interface);
	if (texture_iterator == texture_data.end())
	{
		Load(render_interface);
		texture_dirty = false;
		texture_iterator = texture_data.find(render_interface);
	}
	
	if (texture_dirty)
		Update(render_interface);

	return texture_iterator->second.first;
}

// Returns the dimensions of the resource's texture.
const Vector2i& TextureResource::GetDimensions(RenderInterface* render_interface) const
{
	TextureDataMap::iterator texture_iterator = texture_data.find(render_interface);
	if (texture_iterator == texture_data.end())
	{
		Load(render_interface);
		texture_iterator = texture_data.find(render_interface);
	}

	return texture_iterator->second.second;
}

// Returns the resource's source.
const String& TextureResource::GetSource() const
{
	return source;
}

// Releases the texture's handle.
void TextureResource::Release(RenderInterface* render_interface)
{
	if (render_interface == NULL)
	{
		for (TextureDataMap::iterator texture_iterator = texture_data.begin(); texture_iterator != texture_data.end(); ++texture_iterator)
		{
			TextureHandle handle = texture_iterator->second.first;
			if (handle)
				texture_iterator->first->ReleaseTexture(handle);
		}

		texture_data.clear();
	}
	else
	{
		TextureDataMap::iterator texture_iterator = texture_data.find(render_interface);
		if (texture_iterator == texture_data.end())
			return;

		TextureHandle handle = texture_iterator->second.first;
		if (handle)
			texture_iterator->first->ReleaseTexture(handle);

		texture_data.erase(render_interface);
	}
}

// Attempts to load the texture from the source.
bool TextureResource::Load(RenderInterface* render_interface) const
{
	// Check for special loader tokens.
	if (!source.Empty() &&
		source[0] == '?')
	{
		Vector2i dimensions(0, 0);
		TextureLayoutTexture* texture = NULL;

		// Find the generation protocol and generate the data accordingly.
		String protocol = source.Substring(1, source.Find("::") - 1);
		if (protocol == "font")
		{
			// The requested texture is a font layer.
			FontFaceHandle* handle = NULL;
			FontEffect* layer_id = NULL;
			int texture_id = 0;
			
			if (sscanf(source.CString(), "?font::%p/%p/%d/%p", &handle, &layer_id, &texture_id, &texture) == 4)
			{
				handle->GenerateLayerTexture(layer_id, texture_id);
				dimensions = texture->GetDimensions();
			}
		}

		// If texture data was generated, great! Otherwise, fallback to the LoadTexture() code and
		// hope the client knows what the hell to do with the question mark in their file name.
		if (texture && texture->GetTextureData())
		{
			TextureHandle handle;
			bool success = render_interface->GenerateTexture(handle, texture->GetTextureData(), dimensions);
			if (success)
			{
				texture_data[render_interface] = TextureData(handle, dimensions);
				if (texture->IsFull())
					texture->DeallocateTexture();
				return true;
			}
			else
			{
				Log::Message(Log::LT_WARNING, "Failed to generate internal texture %s.", source.CString());
				texture_data[render_interface] = TextureData(0, Vector2i(0, 0));

				return false;
			}
		}
	}

	TextureHandle handle;
	Vector2i dimensions;
	if (!render_interface->LoadTexture(handle, dimensions, source))
	{
		Log::Message(Log::LT_WARNING, "Failed to load texture from %s.", source.CString());
		texture_data[render_interface] = TextureData(0, Vector2i(0, 0));

		return false;
	}

	texture_data[render_interface] = TextureData(handle, dimensions);
	return true;
}

// Attempts to update the texture.
void TextureResource::Update( RenderInterface* render_interface ) const
{
	if (!source.Empty() && source[0] == '?')
	{
		FontFaceHandle* handle = NULL;
		FontEffect* layer_id = NULL;
		int texture_id = 0;
		TextureLayoutTexture* layout_texture = NULL;

		if (sscanf(source.CString(), "?font::%p/%p/%d/%p", &handle, &layer_id, &texture_id, &layout_texture) == 4)
		{
			Vector2i dimensions(0, 0);
			Vector2i position(0, 0);

			handle->GenerateLayerTexture(layer_id, texture_id);
			const byte* data = layout_texture->GetTextureData(position, dimensions);
			if (!data)
				return;

			TextureDataMap::iterator texture_iterator = texture_data.find(render_interface);
			if (texture_iterator != texture_data.end())
			{
				TextureHandle texHandle = texture_iterator->second.first;
				bool success = render_interface->UpdateTexture(texHandle, data, position, dimensions);
				if (success)
				{
					if (layout_texture->IsFull())
						layout_texture->DeallocateTexture();
				}
				else
				{
					Log::Message(Log::LT_WARNING, "Failed to update internal texture %s.", source.CString());
					texture_data[render_interface] = TextureData(0, Vector2i(0, 0));
				}
			}
		}
	}
	texture_dirty = false;
}

void TextureResource::OnReferenceDeactivate()
{
	Release();
	delete this;
}

}
}
