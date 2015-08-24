# File: Android.mk
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_STATIC_LIBRARIES := ../libemojidex_static
LOCAL_MODULE    := libemojidex
LOCAL_SRC_FILES := libemojidex_wrap.cpp
LOCAL_CFLAGS    := -frtti
LOCAL_C_INCLUDES += SOURCE_DIRECTORY

include $(BUILD_SHARED_LIBRARY)
