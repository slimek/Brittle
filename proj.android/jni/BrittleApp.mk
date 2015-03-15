#
# Load all pre-built libraries
#

CANDY_LIB := $(GIT_ROOT)/CandyJar/lib/Android.Ndk.$(BRITTLE_CONFIG)/$(TARGET_ARCH_ABI)
COCOS_LIB := $(GIT_ROOT)/Cocos2d-x3/lib/Android.Ndk.$(BRITTLE_CONFIG)/$(TARGET_ARCH_ABI)

#
# CandyJar 
#

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

#
# Cocos2d-x
#

include $(CLEAR_VARS)
LOCAL_MODULE := cocos2dx_android_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libcocos2dandroid.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos2dx_internal_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libcocos2dxinternal.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_flatbuffers_static
LOCAL_SRC_FILES := $(COCOS_LIB)/flatbuffers.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libaudioengine_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libaudioengine.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libbox2d_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libbox2d.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libcocos3d_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libcocos3d.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libcocosbuilder_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libcocosbuilder.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libcocosdenshion_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libcocosdenshion.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libcocostudio_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libcocostudio.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libextension_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libextension.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libnetwork_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libnetwork.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libspine_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libspine.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_libui_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libui.a
include $(PREBUILT_STATIC_LIBRARY)

#
# Cocos2d-x External
#

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_chipmunk_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libchipmunk.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_crypto_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_curl_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_freetype_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libfreetype.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_jpeg_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libjpeg.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_png_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libpng.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_ssl_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libssl.a
include $(PREBUILT_STATIC_LIBRARY)



#
# Variables used by App make
#

include $(CLEAR_VARS)

BRITTLE_PREBUILT_STATIC_LIBRARIES := \
	boost-chrono \
	boost-date_time \
	boost-filesystem \
	boost-system \
	cocos2dx_android_static \
	cocos2dx_internal_static \
	cocos_flatbuffers_static \
	cocos_libaudioengine_static \
	cocos_libbox2d_static \
	cocos_libcocos3d_static \
	cocos_libcocosbuilder_static \
	cocos_libcocosdenshion_static \
	cocos_libcocostudio_static \
	cocos_libextension_static \
	cocos_libnetwork_static \
	cocos_libspine_static \
	cocos_libui_static \
	cocos_chipmunk_static \
	cocos_crypto_static \
	cocos_curl_static \
	cocos_freetype_static \
	cocos_jpeg_static \
	cocos_png_static \
	cocos_ssl_static \
	cpufeatures


BRITTLE_LDLIBS := \
	-lGLESv2 \
	-llog \
	-lz \
	-landroid \
	-lEGL \
	-lOpenSLES


BRITTLE_C_INCLUDES := \
	$(GIT_ROOT)/Brittle/include \
	$(GIT_ROOT)/Macaron/include \
	$(GIT_ROOT)/Caramel/include \
	$(GIT_ROOT)/CandyJar/include \
	$(GIT_ROOT)/Cocos2d-x3/cocos \
	$(GIT_ROOT)/Cocos2d-x3/cocos/editor-support \
	$(GIT_ROOT)/Cocos2d-x3/cocos/platform/android  \
	$(GIT_ROOT)/Cocos2d-x3/external/chipmunk \
	$(GIT_ROOT)/Cocos2d-x3/external/curl \
	$(GIT_ROOT)/Cocos2d-x3/external/freetype2/include/android 

