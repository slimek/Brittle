#
# Load all pre-built libraries
#

CANDY_LIB := $(GIT_ROOT)/CandyJar/lib/Android.Ndk.$(BRITTLE_CONFIG)/$(TARGET_ARCH_ABI)
COCOS_LIB := $(GIT_ROOT)/Cocos2d-x3/lib/Android.Ndk.$(BRITTLE_CONFIG)/$(TARGET_ARCH_ABI)

include $(CLEAR_VARS)
LOCAL_MODULE := boost-chrono
LOCAL_SRC_FILES := $(CANDY_LIB)/libboost-chrono.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := boost-date_time
LOCAL_SRC_FILES := $(CANDY_LIB)/libboost-date_time.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := boost-filesystem
LOCAL_SRC_FILES := $(CANDY_LIB)/libboost-filesystem.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := boost-system
LOCAL_SRC_FILES := $(CANDY_LIB)/libboost-system.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos2dx_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libcocos2d.a
include $(PREBUILT_STATIC_LIBRARY)


#
# Variables used by App make
#

BRITTLE_PREBUILT_STATIC_LIBRARIES := \
	boost-chrono \
	boost-data_time \
	boost-filesystem \
	boost-system \
	cocos2dx_static


BRITTLE_LDLIBS := \
	-lGLESv2 \
	-llog \
	-lz


BRITTLE_C_INCLUDES := 
	$(GIT_ROOT)/Brittle/include \
	$(GIT_ROOT)/Caramel/include \
	$(GIT_ROOT)/CandyJar/include \
	$(GIT_ROOT)/Cocos2d-x3/cocos/editor-supprot \
	$(GIT_ROOT)/Cocos2d-x3/cocos
	