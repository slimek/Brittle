LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Brittle

BRT_SRC := ../../src

# LOCAL_PCH := $(BRT_SRC)/BrittlePch.h

LOCAL_SRC_FILES := \
	$(BRT_SRC)/BrittlePch.cpp \
	$(BRT_SRC)/Actions.cpp \
	$(BRT_SRC)/Animation.cpp \
	$(BRT_SRC)/Core.cpp \
	$(BRT_SRC)/Layout.cpp \
	$(BRT_SRC)/Nodes.cpp \
	$(BRT_SRC)/Ui.cpp \
	$(BRT_SRC)/Utils.cpp \
	$(BRT_SRC).android/Core_android.cpp
	
	
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../../src \
	$(LOCAL_PATH)/../../include \
	$(GIT_ROOT)/Macaron/include \
	$(GIT_ROOT)/Caramel/include \
	$(GIT_ROOT)/CandyJar/include \
	$(GIT_ROOT)/Cocos2d-x3/cocos/platform/android \
	$(GIT_ROOT)/Cocos2d-x3/cocos


include $(BUILD_STATIC_LIBRARY)
