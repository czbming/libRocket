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

#include "ChatBox.h"
#include <Rocket/Core.h>
#include <rocket/Controls.h>

extern Rocket::Core::Context* context;

ChatBox::ChatBox(Language lang) : curr_lang(lang), document(NULL), disp_element(NULL), form_element(NULL)
{
	font_infos[LANG_EN].font_file = "../../assets/Delicious-Roman.otf";
	font_infos[LANG_EN].font_face_index = 0;
	font_infos[LANG_EN].rml_file = "data/chat_box_en.rml";

	font_infos[LANG_ZH_HANS].font_file = "data/msyh.ttc";
	font_infos[LANG_ZH_HANS].font_face_index = 0;
	font_infos[LANG_ZH_HANS].rml_file = "data/chat_box_zh-Hans.rml";

	font_infos[LANG_ZH_HANT].font_file = "data/msjh.ttc";
	font_infos[LANG_ZH_HANT].font_face_index = 0;
	font_infos[LANG_ZH_HANT].rml_file = "data/chat_box_zh-Hant.rml";

	font_infos[LANG_DE].font_file = "../../assets/Delicious-Roman.otf";
	font_infos[LANG_DE].font_face_index = 0;
	font_infos[LANG_DE].rml_file = "data/chat_box_de.rml";

	font_infos[LANG_ES].font_file = "../../assets/Delicious-Roman.otf";
	font_infos[LANG_ES].font_face_index = 0;
	font_infos[LANG_ES].rml_file = "data/chat_box_es.rml";

	font_infos[LANG_FR].font_file = "../../assets/Delicious-Roman.otf";
	font_infos[LANG_FR].font_face_index = 0;
	font_infos[LANG_FR].rml_file = "data/chat_box_fr.rml";

	font_infos[LANG_IT].font_file = "../../assets/Delicious-Roman.otf";
	font_infos[LANG_IT].font_face_index = 0;
	font_infos[LANG_IT].rml_file = "data/chat_box_it.rml";

	font_infos[LANG_NL].font_file = "../../assets/Delicious-Roman.otf";
	font_infos[LANG_NL].font_face_index = 0;
	font_infos[LANG_NL].rml_file = "data/chat_box_nl.rml";

	font_infos[LANG_JA].font_file = "data/meiryo.ttc";
	font_infos[LANG_JA].font_face_index = 2;
	font_infos[LANG_JA].rml_file = "data/chat_box_ja.rml";

	font_infos[LANG_KO].font_file = "data/malgun.ttf";
	font_infos[LANG_KO].font_face_index = 0;
	font_infos[LANG_KO].rml_file = "data/chat_box_ko.rml";

	font_infos[LANG_RU].font_file = "data/segoeui.ttf";
	font_infos[LANG_RU].font_face_index = 0;
	font_infos[LANG_RU].rml_file = "data/chat_box_ru.rml";

	SetLanguage(lang);
}

ChatBox::~ChatBox()
{
	Clear();
}

void ChatBox::SetLanguage( Language lang )
{
	if (curr_lang == lang && document)
		return;

	FontInfo& info = font_infos[lang];
	if (info.rml_file.Empty())
		return;

	Clear();

	Rocket::Core::FontDatabase::LoadFontFace(info.font_file, info.font_face_index);
	document = context->LoadDocument(info.rml_file);
	if (document)
	{
		document->Show();
		document->RemoveReference();

		disp_element = document->GetElementById("display");
		form_element = document->GetElementById("input");
		if (form_element)
			form_element->AddEventListener("submit", this);
	}
	curr_lang = lang;
}

void ChatBox::Clear()
{
	if (form_element)
	{
		form_element->RemoveEventListener("submit", this);
		form_element = NULL;
		disp_element = NULL;
	}

	if (document)
	{
		Rocket::Core::String face_name = document->GetProperty<Rocket::Core::String>("font-family");
		context->UnloadDocument(document);
		document = NULL;
		Rocket::Core::FontDatabase::UnloadFontFace(face_name);
	}
}

void ChatBox::ProcessEvent(Rocket::Core::Event& event)
{
	if (event == "submit")
	{
		Rocket::Core::String value = event.GetParameter<Rocket::Core::String>("submit", "");
		if (value == "switch language")
		{
			Language next_lang = static_cast<Language>((curr_lang + 1) % LANG_SIZE);
			SetLanguage(next_lang);
		}
		else if (value == "send text")
		{
			Rocket::Controls::ElementFormControlInput* edit_box = dynamic_cast<Rocket::Controls::ElementFormControlInput*>(form_element->GetChild(1));
			if (edit_box && !edit_box->GetValue().Empty())
			{
				Rocket::Core::Element* p = document->CreateElement("p");
				if (p)
				{
					p->SetInnerRML(edit_box->GetValue());
					disp_element->AppendChild(p);
					p->ScrollIntoView();
					p->RemoveReference();
				}

				edit_box->SetValue("");
				edit_box->Focus();
			}
		}
	}
}
