# File: Android.mk
LOCAL_PATH := $(call my-dir)
OR_LIB_PATH := LOCAL_PATH
OR_INCLUDE_PATH := LOCAL_PATH
OR_CPP_SOURCES :=

include $(CLEAR_VARS)
#TARGET_ARCH 	:= arm
#TARGET_ARCH_ABI := armeabi
TARGET_PLATFORM := android-21
#TARGET_ABI		:= android-21-armeabi

LOCAL_MODULE    := libemojidex_shared
LOCAL_SRC_FILES := libemojidex_wrap.cpp $(OR_CPP_SOURCES)
LOCAL_CPP_FEATURES += exceptions rtti pthread
#LOCAL_CFLAGS    := -frtti -fexceptions
LOCAL_C_INCLUDES += $(OR_INCLUDE_PATH)

#$(call import-add-path, $(OR_LIB_PATH))
#LOCAL_STATIC_LIBRARIES 	:= boost_system-gcc-mt-1_53 boost_filesystem-gcc-mt-1_53 ssl crypto

LOCAL_LDLIBS 	:= -L$(OR_LIB_PATH) -lboost_system -lboost_filesystem -lz -lssl -lcrypto
#LOCAL_STATIC_LIBRARIES := emojidex_static

include $(BUILD_SHARED_LIBRARY)
