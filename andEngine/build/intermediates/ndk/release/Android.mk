LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := andengine_shared
LOCAL_SRC_FILES := \
	/Users/stephanohuguestelolahy/Documents/Github/SampleAndEngine/andEngine/src/main/jni/Android.mk \
	/Users/stephanohuguestelolahy/Documents/Github/SampleAndEngine/andEngine/src/main/jni/Application.mk \
	/Users/stephanohuguestelolahy/Documents/Github/SampleAndEngine/andEngine/src/main/jni/build.sh \
	/Users/stephanohuguestelolahy/Documents/Github/SampleAndEngine/andEngine/src/main/jni/src/BufferUtils.cpp \
	/Users/stephanohuguestelolahy/Documents/Github/SampleAndEngine/andEngine/src/main/jni/src/GLES20Fix.c \

LOCAL_C_INCLUDES += /Users/stephanohuguestelolahy/Documents/Github/SampleAndEngine/andEngine/src/main/jni
LOCAL_C_INCLUDES += /Users/stephanohuguestelolahy/Documents/Github/SampleAndEngine/andEngine/src/release/jni

include $(BUILD_SHARED_LIBRARY)
