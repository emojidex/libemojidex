
LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)

LOCAL_MODULE := msgpack
LOCAL_C_INCLUDES := $(LOCAL_PATH)/src/
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/src/
LOCAL_CPPFLAGS += -fexceptions
LOCAL_SRC_FILES := \
src/object.cpp \
src/objectc.c \
src/unpack.c \
src/version.c \
src/vrefbuffer.c \
src/zone.c

include $(BUILD_SHARED_LIBRARY)