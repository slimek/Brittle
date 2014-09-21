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

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_ui_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libui.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_android_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libcocos2dandroid.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_extension_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libextension.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := chipmunk_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libchipmunk.a
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
LOCAL_MODULE := cocos_tiff_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libtiff.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_webp_static
LOCAL_SRC_FILES := $(COCOS_LIB)/libwebp.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Caramel
LOCAL_SRC_FILES := $(GIT_ROOT)/Caramel/proj.android/obj/$(BRITTLE_CONFIG)/local/$(TARGET_ARCH_ABI)/libCaramel.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Macaron
LOCAL_SRC_FILES := $(GIT_ROOT)/Macaron/proj.android/obj/$(BRITTLE_CONFIG)/local/$(TARGET_ARCH_ABI)/libMacaron.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Brittle
LOCAL_SRC_FILES := $(GIT_ROOT)/Brittle/proj.android/obj/$(BRITTLE_CONFIG)/local/$(TARGET_ARCH_ABI)/libBrittle.a
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
	cocos2dx_static \
	cocos_ui_static \
	cocos_android_static \
	cocos_extension_static \
	chipmunk_static \
	cocos_curl_static \
	cocos_freetype_static \
	cocos_jpeg_static \
	cocos_png_static \
	cocos_tiff_static \
	cocos_webp_static \
	Caramel \
	Macaron \
	Brittle


BRITTLE_LDLIBS := \
	-lGLESv2 \
	-lEGL \
	-llog \
	-lz \
	-landroid


BRITTLE_C_INCLUDES := \
	$(GIT_ROOT)/Brittle/include \
	$(GIT_ROOT)/Macaron/include \
	$(GIT_ROOT)/Caramel/include \
	$(GIT_ROOT)/CandyJar/include \
	$(GIT_ROOT)/Cocos2d-x3/cocos/platform/android \
	$(GIT_ROOT)/Cocos2d-x3/cocos/editor-supprot \
	$(GIT_ROOT)/Cocos2d-x3/cocos
	