LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := rocketcontrols_shared

LOCAL_MODULE_FILENAME := librocketcontrols

LOCAL_SRC_FILES := Clipboard.cpp \
					Controls.cpp \
					DataFormatter.cpp \
					DataQuery.cpp \
					DataSource.cpp \
					DataSourceListener.cpp \
					ElementDataGrid.cpp \
					ElementDataGridCell.cpp \
					ElementDataGridExpandButton.cpp \
					ElementDataGridRow.cpp \
					ElementForm.cpp \
					ElementFormControl.cpp \
					ElementFormControlDataSelect.cpp \
					ElementFormControlInput.cpp \
					ElementFormControlSelect.cpp \
					ElementFormControlTextArea.cpp \
					ElementTabSet.cpp \
					ElementTextSelection.cpp \
					InputType.cpp \
					InputTypeButton.cpp \
					InputTypeCheckbox.cpp \
					InputTypeRadio.cpp \
					InputTypeRange.cpp \
					InputTypeSubmit.cpp \
					InputTypeText.cpp \
					SelectOption.cpp \
					WidgetDropDown.cpp \
					WidgetSlider.cpp \
					WidgetSliderInput.cpp \
					WidgetTextInput.cpp \
					WidgetTextInputMultiLine.cpp \
					WidgetTextInputSingleLine.cpp \
					WidgetTextInputSingleLinePassword.cpp \
					XMLNodeHandlerDataGrid.cpp \
					XMLNodeHandlerTabSet.cpp \
					XMLNodeHandlerTextArea.cpp

LOCAL_SHARED_LIBRARIES := rocketcore_shared

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/. $(LOCAL_PATH)/../../include

include $(BUILD_SHARED_LIBRARY)

$(call import-module,libRocket/Source/Core)
