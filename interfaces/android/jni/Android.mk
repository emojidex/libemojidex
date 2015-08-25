# File: Android.mk
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := libemojidex_shared
LOCAL_SRC_FILES := libemojidex_wrap.cpp
LOCAL_CFLAGS    := -frtti -fexceptions
LOCAL_C_INCLUDES += SOURCE_DIRECTORY
LOCAL_LDLIBS := -L$(LOCAL_PATH)/../ -lemojidex_static
LOCAL_STATIC_LIBRARIES := emojidex_static

include $(BUILD_SHARED_LIBRARY)
