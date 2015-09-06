# File: Android.mk
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
TARGET_ARCH 	:= arm
TARGET_ARCH_ABI := armeabi
TARGET_PLATFORM := android-21
TARGET_ABI		:= android-21-armeabi

LOCAL_MODULE    := libemojidex_shared
LOCAL_SRC_FILES := libemojidex_wrap.cpp #CPP_SOURCES
LOCAL_CFLAGS    := -frtti -fexceptions
LOCAL_C_INCLUDES += #SOURCE_DIRECTORY
LOCAL_LDLIBS 	:= -L$(LOCAL_PATH)/../natives/arm/ -lboost
LOCAL_STATIC_LIBRARIES := emojidex_static

include $(BUILD_SHARED_LIBRARY)
