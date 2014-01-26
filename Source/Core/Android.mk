LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := rocketcore_shared

LOCAL_MODULE_FILENAME := librocketcore

LOCAL_SRC_FILES := BaseXMLParser.cpp \
					Box.cpp \
					Clock.cpp \
					Context.cpp \
					ContextInstancer.cpp \
					ContextInstancerDefault.cpp \
					ConvolutionFilter.cpp \
					Core.cpp \
					Decorator.cpp \
					DecoratorInstancer.cpp \
					DecoratorNone.cpp \
					DecoratorNoneInstancer.cpp \
					DecoratorTiled.cpp \
					DecoratorTiledBox.cpp \
					DecoratorTiledBoxInstancer.cpp \
					DecoratorTiledHorizontal.cpp \
					DecoratorTiledHorizontalInstancer.cpp \
					DecoratorTiledImage.cpp \
					DecoratorTiledImageInstancer.cpp \
					DecoratorTiledInstancer.cpp \
					DecoratorTiledVertical.cpp \
					DecoratorTiledVerticalInstancer.cpp \
					Dictionary.cpp \
					DocumentHeader.cpp \
					Element.cpp \
					ElementBackground.cpp \
					ElementBorder.cpp \
					ElementDecoration.cpp \
					ElementDefinition.cpp \
					ElementDocument.cpp \
					ElementHandle.cpp \
					ElementImage.cpp \
					ElementInstancer.cpp \
					ElementReference.cpp \
					ElementScroll.cpp \
					ElementStyle.cpp \
					ElementStyleCache.cpp \
					ElementText.cpp \
					ElementTextDefault.cpp \
					ElementUtilities.cpp \
					Event.cpp \
					EventDispatcher.cpp \
					EventInstancer.cpp \
					EventInstancerDefault.cpp \
					EventListenerInstancer.cpp \
					Factory.cpp \
					FileInterface.cpp \
					FileInterfaceDefault.cpp \
					FontDatabase.cpp \
					FontEffect.cpp \
					FontEffectInstancer.cpp \
					FontEffectNone.cpp \
					FontEffectNoneInstancer.cpp \
					FontEffectOutline.cpp \
					FontEffectOutlineInstancer.cpp \
					FontEffectShadow.cpp \
					FontEffectShadowInstancer.cpp \
					FontFace.cpp \
					FontFaceHandle.cpp \
					FontFaceLayer.cpp \
					FontFamily.cpp \
					Geometry.cpp \
					GeometryDatabase.cpp \
					GeometryUtilities.cpp \
					LayoutBlockBox.cpp \
					LayoutBlockBoxSpace.cpp \
					LayoutEngine.cpp \
					LayoutInlineBox.cpp \
					LayoutInlineBoxText.cpp \
					LayoutLineBox.cpp \
					Log.cpp \
					Math.cpp \
					Plugin.cpp \
					PluginRegistry.cpp \
					precompiled.cpp \
					Property.cpp \
					PropertyDefinition.cpp \
					PropertyDictionary.cpp \
					PropertyParserColour.cpp \
					PropertyParserKeyword.cpp \
					PropertyParserNumber.cpp \
					PropertyParserString.cpp \
					PropertySpecification.cpp \
					ReferenceCountable.cpp \
					RenderInterface.cpp \
					Stream.cpp \
					StreamFile.cpp \
					StreamMemory.cpp \
					String.cpp \
					StringCache.cpp \
					StringUtilities.cpp \
					StyleSheet.cpp \
					StyleSheetFactory.cpp \
					StyleSheetNode.cpp \
					StyleSheetNodeSelector.cpp \
					StyleSheetNodeSelectorEmpty.cpp \
					StyleSheetNodeSelectorFirstChild.cpp \
					StyleSheetNodeSelectorFirstOfType.cpp \
					StyleSheetNodeSelectorLastChild.cpp \
					StyleSheetNodeSelectorLastOfType.cpp \
					StyleSheetNodeSelectorNthChild.cpp \
					StyleSheetNodeSelectorNthLastChild.cpp \
					StyleSheetNodeSelectorNthLastOfType.cpp \
					StyleSheetNodeSelectorNthOfType.cpp \
					StyleSheetNodeSelectorOnlyChild.cpp \
					StyleSheetNodeSelectorOnlyOfType.cpp \
					StyleSheetParser.cpp \
					StyleSheetSpecification.cpp \
					SystemInterface.cpp \
					Template.cpp \
					TemplateCache.cpp \
					Texture.cpp \
					TextureDatabase.cpp \
					TextureLayout.cpp \
					TextureLayoutRectangle.cpp \
					TextureLayoutRow.cpp \
					TextureLayoutTexture.cpp \
					TextureResource.cpp \
					UnicodeRange.cpp \
					URL.cpp \
					Variant.cpp \
					Vector2.cpp \
					WidgetSlider.cpp \
					WidgetSliderScroll.cpp \
					WString.cpp \
					XMLNodeHandler.cpp \
					XMLNodeHandlerBody.cpp \
					XMLNodeHandlerDefault.cpp \
					XMLNodeHandlerHead.cpp \
					XMLNodeHandlerTemplate.cpp \
					XMLParser.cpp \
					XMLParseTools.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := freetype_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/. $(LOCAL_PATH)/../../include

include $(BUILD_SHARED_LIBRARY)

$(call import-module,support)
