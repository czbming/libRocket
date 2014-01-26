LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := rocketdebugger_shared

LOCAL_MODULE_FILENAME := librocketdebugger

LOCAL_SRC_FILES := Debugger.cpp \
					ElementContextHook.cpp \
					ElementInfo.cpp \
					ElementLog.cpp \
					Geometry.cpp \
					Plugin.cpp \
					SystemInterface.cpp

LOCAL_SHARED_LIBRARIES := rocketcore_shared

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/. $(LOCAL_PATH)/../../include

include $(BUILD_SHARED_LIBRARY)

$(call import-module,libRocket/Source/Core)
