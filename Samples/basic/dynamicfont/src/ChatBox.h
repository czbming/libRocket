/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2014 Wantu Networks Ltd
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

#ifndef CHATBOX_H
#define CHATBOX_H

#include <Rocket/Core/EventListener.h>
#include <Rocket/Core/ElementDocument.h>

/**
	@author Chen Zhibiao
 */

class ChatBox : public Rocket::Core::EventListener
{
public:
	enum Language
	{
		LANG_EN,
		LANG_ZH_HANS,
		LANG_ZH_HANT,
		LANG_DE,
		LANG_ES,
		LANG_FR,
		LANG_IT,
		LANG_NL,
		LANG_JA,
		LANG_KO,
		LANG_RU,
		LANG_SIZE
	};

	explicit ChatBox(Language lang = LANG_EN);
	virtual ~ChatBox();

protected:
	void SetLanguage(Language lang);
	void Clear();
	virtual void ProcessEvent(Rocket::Core::Event& event);

	struct FontInfo
	{
		Rocket::Core::String font_file;
		int font_face_index;
		Rocket::Core::String rml_file;
	}; 

	FontInfo font_infos[LANG_SIZE];
	Language curr_lang;

	Rocket::Core::ElementDocument* document;
	Rocket::Core::Element* disp_element;
	Rocket::Core::Element* form_element;
};

#endif
